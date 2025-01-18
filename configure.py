#!/usr/bin/env python3

###
# Generates build files for the project.
# This file also includes the project configuration,
# such as compiler flags and the object matching status.
#
# Usage:
#   python3 configure.py
#   ninja
#
# Append --help to see available options.
###

import argparse
import sys
from pathlib import Path
from typing import Any, Dict, List

from tools.project import (
    Object,
    ProgressCategory,
    ProjectConfig,
    calculate_progress,
    generate_build,
    is_windows,
)

# Game versions
DEFAULT_VERSION = 0
VERSIONS = [
    "WPSE",
]

parser = argparse.ArgumentParser()
parser.add_argument(
    "mode",
    choices=["configure", "progress"],
    default="configure",
    help="script mode (default: configure)",
    nargs="?",
)
parser.add_argument(
    "-v",
    "--version",
    choices=VERSIONS,
    type=str.upper,
    default=VERSIONS[DEFAULT_VERSION],
    help="version to build",
)
parser.add_argument(
    "--build-dir",
    metavar="DIR",
    type=Path,
    default=Path("build"),
    help="base build directory (default: build)",
)
parser.add_argument(
    "--binutils",
    metavar="BINARY",
    type=Path,
    help="path to binutils (optional)",
)
parser.add_argument(
    "--compilers",
    metavar="DIR",
    type=Path,
    help="path to compilers (optional)",
)
parser.add_argument(
    "--map",
    action="store_true",
    help="generate map file(s)",
)
parser.add_argument(
    "--debug",
    action="store_true",
    help="build with debug info (non-matching)",
)
if not is_windows():
    parser.add_argument(
        "--wrapper",
        metavar="BINARY",
        type=Path,
        help="path to wibo or wine (optional)",
    )
parser.add_argument(
    "--dtk",
    metavar="BINARY | DIR",
    type=Path,
    help="path to decomp-toolkit binary or source (optional)",
)
parser.add_argument(
    "--objdiff",
    metavar="BINARY | DIR",
    type=Path,
    help="path to objdiff-cli binary or source (optional)",
)
parser.add_argument(
    "--sjiswrap",
    metavar="EXE",
    type=Path,
    help="path to sjiswrap.exe (optional)",
)
parser.add_argument(
    "--verbose",
    action="store_true",
    help="print verbose output",
)
parser.add_argument(
    "--non-matching",
    dest="non_matching",
    action="store_true",
    help="builds equivalent (but non-matching) or modded objects",
)
parser.add_argument(
    "--no-progress",
    dest="progress",
    action="store_false",
    help="disable progress calculation",
)
args = parser.parse_args()

config = ProjectConfig()
config.version = str(args.version)
version_num = VERSIONS.index(config.version)

# Apply arguments
config.build_dir = args.build_dir
config.dtk_path = args.dtk
config.objdiff_path = args.objdiff
config.binutils_path = args.binutils
config.compilers_path = args.compilers
config.generate_map = args.map
config.non_matching = args.non_matching
config.sjiswrap_path = args.sjiswrap
config.progress = args.progress
if not is_windows():
    config.wrapper = args.wrapper
# Don't build asm unless we're --non-matching
if not config.non_matching:
    config.asm_dir = None

# Tool versions
config.binutils_tag = "2.42-1"
config.compilers_tag = "20240706"
config.dtk_tag = "v1.3.0"
config.objdiff_tag = "v2.4.0"
config.sjiswrap_tag = "v1.2.0"
config.wibo_tag = "0.6.11"

# Project
config.config_path = Path("config") / config.version / "config.yml"
config.check_sha_path = Path("config") / config.version / "build.sha1"
config.asflags = [
    "-mgekko",
    "--strip-local-absolute",
    "-I include",
    f"-I build/{config.version}/include",
    f"--defsym BUILD_VERSION={version_num}",
    f"--defsym VERSION_{config.version}",
]
config.ldflags = [
    "-fp hardware",
    "-nodefaults",
]
if args.debug:
    config.ldflags.append("-gdwarf-2")
if args.map:
    config.ldflags.append("-mapunused")
    # config.ldflags.append("-listclosure") # For Wii linkers

# Use for any additional files that should cause a re-configure when modified
config.reconfig_deps = []

# Optional numeric ID for decomp.me preset
# Can be overridden in libraries or objects
config.scratch_preset_id = None

# Base flags, common to most GC/Wii games.
# Generally leave untouched, with overrides added below.
cflags_base = [
    "-nodefaults",
    "-proc gekko",
    "-align powerpc",
    "-enum int",
    "-fp hardware",
    "-Cpp_exceptions off",
    # "-W all",
    "-O4,p",
    "-inline auto",
    '-pragma "cats off"',
    '-pragma "warn_notinlined off"',
    "-maxerrors 1",
    "-nosyspath",
    "-RTTI off",
    "-fp_contract on",
    "-str reuse",
    "-enc SJIS",
    "-i include",
    "-i libs/PowerPC_EABI_Support/include/stl",
    "-i libs/PowerPC_EABI_Support/include/",
    "-i libs/RVL_SDK/include/",
    "-i libs/nw4r/include/",
    f"-i build/{config.version}/include",
    f"-DBUILD_VERSION={version_num}",
    f"-DVERSION_{config.version}",
]

# Debug flags
if args.debug:
    cflags_base.extend(["-sym dwarf-2", "-DDEBUG=1"])
else:
    cflags_base.append("-DNDEBUG=1")

# Metrowerks library flags
cflags_runtime = [
    *cflags_base,
    "-use_lmw_stmw on",
    "-str reuse,pool,readonly",
    "-common off",
    "-inline on",
    "-func_align 4",
]

# Metrowerks C standard library flags
cflags_mslc = [
    *cflags_base,
    "-use_lmw_stmw on",
    "-str reuse,pool,readonly",
    "-fp_contract off",
    "-inline on",
    "-ipa file",
    "-func_align 4",
    "-i libs/RVL_SDK/include/",
]

cflags_game = [
    *cflags_base,
    "-Cpp_exceptions on",
    # "-RTTI on",
    "-sdata 0",
    "-sdata2 0",
]

config.linker_version = "GC/1.3.2"


# Helper function for Dolphin libraries
def DolphinLib(lib_name: str, objects: List[Object]) -> Dict[str, Any]:
    return {
        "lib": lib_name,
        "mw_version": "Wii/1.1",
        "src_dir": "libs/RVL_SDK/src",
        "cflags": cflags_base,
        # "cflags": cflags_sdk + extra_cflags,
        "progress_category": "sdk",
        "objects": objects,
    }


# Helper function for game objects
def Game(objects: List[Object]) -> Dict[str, Any]:
    return {
        "lib": "Pokemon Rumble",
        "mw_version": "Wii/1.1",
        "src_dir": "src",
        "cflags": cflags_game,
        "progress_category": "game",
        "objects": objects,
    }


Matching = True                   # Object matches and should be linked
NonMatching = False               # Object does not match and should not be linked
Equivalent = config.non_matching  # Object should be linked when configured with --non-matching


# Object is only matching for specific versions
def MatchingFor(*versions):
    return config.version in versions


config.warn_missing_config = True
config.warn_missing_source = False
config.libs = [
    Game([
        Object(NonMatching, "piiStat.cpp"),
        Object(NonMatching, "ks_alloc.cpp")
    ]),
    {
        "lib": "Runtime.PPCEABI.H",
        "mw_version": "Wii/1.1",
        "src_dir": "libs/PowerPC_EABI_Support/src",
        "cflags": cflags_runtime,
        "progress_category": "sdk",
        "objects": [
            Object(Matching, "Runtime/__mem.c"),
            # Object(NonMatching, "Runtime/__va_arg.c"),
            # Object(NonMatching, "Runtime/global_destructor_chain.c"),
            # Object(NonMatching, "Runtime/New.cp", extra_cflags = ["-Cpp_exceptions on", "-RTTI on"]),
            Object(NonMatching, "Runtime/NMWException.cp", extra_cflags = ["-Cpp_exceptions on"]),
            Object(Matching, "Runtime/ptmf.c"),
            Object(NonMatching, "Runtime/MWRTTI.cp", extra_cflags = ["-Cpp_exceptions on", "-RTTI on"]),
            Object(NonMatching, "Runtime/runtime.c"),
            # Object(NonMatching, "Runtime/__init_cpp_exceptions.cpp"),
            Object(NonMatching, "Runtime/Gecko_ExceptionPPC.cp", extra_cflags = ["-Cpp_exceptions on"]),
            # Object(NonMatching, "Runtime/GCN_mem_alloc.c"),
        ],
    },
    {
        "lib": "MSL_C.PPCEABI.bare.H",
        "mw_version": "Wii/1.1",
        "src_dir": "libs/PowerPC_EABI_Support/src",
        "cflags": cflags_mslc,
        "progress_category": "sdk",
        "objects": [
            Object(NonMatching, "MSL_C/MSL_Common/alloc.c"),
            # Object(NonMatching, "MSL_C/MSL_Common/ansi_files.c"),
            # Object(NonMatching, "MSL_C/MSL_Common_Embedded/ansi_fp.c"),
            # Object(NonMatching, "MSL_C/MSL_Common/arith.c"),
            # Object(NonMatching, "MSL_C/MSL_Common/assert.c"), #JP only
            # Object(NonMatching, "MSL_C/MSL_Common/buffer_io.c"),
            # Object(NonMatching, "MSL_C/MSL_Common/ctype.c"),
            # Object(NonMatching, "MSL_C/MSL_Common/direct_io.c"),
            # Object(NonMatching, "MSL_C/MSL_Common/errno.c"),
            # Object(NonMatching, "MSL_C/MSL_Common/file_io.c"),
            # Object(NonMatching, "MSL_C/MSL_Common/FILE_POS.c"),
            # Object(NonMatching, "MSL_C/MSL_Common/locale.c"),
            # Object(NonMatching, "MSL_C/MSL_Common/mbstring.c"),
            # Object(NonMatching, "MSL_C/MSL_Common/mem.c"),
            # Object(NonMatching, "MSL_C/MSL_Common/mem_funcs.c"),
            # Object(NonMatching, "MSL_C/MSL_Common/math_api.c"),
            # Object(NonMatching, "MSL_C/MSL_Common/misc_io.c"),
            # Object(NonMatching, "MSL_C/MSL_Common/printf.c"),
            # Object(NonMatching, "MSL_C/MSL_Common/rand.c"),
            # Object(NonMatching, "MSL_C/MSL_Common/float.c"),
            # Object(NonMatching, "MSL_C/MSL_Common/scanf.c"),
            # Object(NonMatching, "MSL_C/MSL_Common/signal.c"),
            # Object(NonMatching, "MSL_C/MSL_Common/string.c"),
            # Object(NonMatching, "MSL_C/MSL_Common/strtold.c"),
            # Object(NonMatching, "MSL_C/MSL_Common/strtoul.c"),
            # Object(NonMatching, "MSL_C/MSL_Common/wcstoul.c"),
            # Object(NonMatching, "MSL_C/MSL_Common/wctype.c"),
            # Object(NonMatching, "MSL_C/MSL_Common/wmem.c"),
            # Object(NonMatching, "MSL_C/MSL_Common/wprintf.c"),
            # Object(NonMatching, "MSL_C/MSL_Common/wscanf.c"),
            # Object(NonMatching, "MSL_C/MSL_Common/wstring.c"),
            # Object(NonMatching, "MSL_C/MSL_Common/wchar_io.c"),
            # Object(NonMatching, "MSL_C/PPC_EABI/uart_console_io_gcn.c"),
            # Object(NonMatching, "MSL_C/PPC_EABI/abort_exit_ppc_eabi.c"),
            # Object(NonMatching, "MSL_C/MSL_Common/secure_error.c"),
            # Object(NonMatching, "MSL_C/MSL_Common/math_double.c"),
            # Object(NonMatching, "MSL_C/MSL_Common_Embedded/math_sun.c"),
            # Object(NonMatching, "MSL_C/MSL_Common_Embedded/Math/Double_precision/e_acos.c"),
            # Object(NonMatching, "MSL_C/MSL_Common_Embedded/Math/Double_precision/e_asin.c"),
            # Object(NonMatching, "MSL_C/MSL_Common_Embedded/Math/Double_precision/e_atan2.c"),
            # Object(NonMatching, "MSL_C/MSL_Common_Embedded/Math/Double_precision/e_fmod.c"),
            # Object(NonMatching, "MSL_C/MSL_Common_Embedded/Math/Double_precision/e_log.c"),
            # Object(NonMatching, "MSL_C/MSL_Common_Embedded/Math/Double_precision/e_log10.c"),
            # Object(NonMatching, "MSL_C/MSL_Common_Embedded/Math/Double_precision/e_pow.c"),
            # Object(NonMatching, "MSL_C/MSL_Common_Embedded/Math/Double_precision/e_rem_pio2.c"),
            # Object(NonMatching, "MSL_C/MSL_Common_Embedded/Math/Double_precision/k_cos.c"),
            # Object(NonMatching, "MSL_C/MSL_Common_Embedded/Math/Double_precision/k_rem_pio2.c"),
            # Object(NonMatching, "MSL_C/MSL_Common_Embedded/Math/Double_precision/k_sin.c"),
            # Object(NonMatching, "MSL_C/MSL_Common_Embedded/Math/Double_precision/k_tan.c"),
            # Object(NonMatching, "MSL_C/MSL_Common_Embedded/Math/Double_precision/s_atan.c"),
            # Object(NonMatching, "MSL_C/MSL_Common_Embedded/Math/Double_precision/s_ceil.c"),
            # Object(NonMatching, "MSL_C/MSL_Common_Embedded/Math/Double_precision/s_copysign.c"),
            # Object(NonMatching, "MSL_C/MSL_Common_Embedded/Math/Double_precision/s_cos.c"),
            # Object(NonMatching, "MSL_C/MSL_Common_Embedded/Math/Double_precision/s_floor.c"),
            # Object(NonMatching, "MSL_C/MSL_Common_Embedded/Math/Double_precision/s_frexp.c"),
            # Object(NonMatching, "MSL_C/MSL_Common_Embedded/Math/Double_precision/s_ldexp.c"),
            # Object(NonMatching, "MSL_C/MSL_Common_Embedded/Math/Double_precision/s_modf.c"),
            # Object(NonMatching, "MSL_C/MSL_Common_Embedded/Math/Double_precision/s_sin.c"),
            # Object(NonMatching, "MSL_C/MSL_Common_Embedded/Math/Double_precision/s_tan.c"),
            # Object(NonMatching, "MSL_C/MSL_Common_Embedded/Math/Double_precision/w_acos.c"),
            # Object(NonMatching, "MSL_C/MSL_Common_Embedded/Math/Double_precision/w_asin.c"),
            # Object(NonMatching, "MSL_C/MSL_Common_Embedded/Math/Double_precision/w_atan2.c"),
            # Object(NonMatching, "MSL_C/MSL_Common_Embedded/Math/Double_precision/w_fmod.c"),
            # Object(NonMatching, "MSL_C/MSL_Common_Embedded/Math/Double_precision/w_log.c"),
            # Object(NonMatching, "MSL_C/MSL_Common_Embedded/Math/Double_precision/w_log10.c"),
            # Object(NonMatching, "MSL_C/MSL_Common_Embedded/Math/Double_precision/w_pow.c"),
            # Object(NonMatching, "MSL_C/MSL_Common_Embedded/Math/Double_precision/e_sqrt.c"),
            # Object(NonMatching, "MSL_C/PPC_EABI/math_ppc.c"),
            # Object(NonMatching, "MSL_C/MSL_Common_Embedded/Math/Double_precision/w_sqrt.c"),
            # Object(NonMatching, "MSL_C/MSL_Common/extras.c"),
        ],
    },
    DolphinLib(
        "fs",
        [
            Object(NonMatching, "revolution/fs/fs.c"),
        ],
    ),
    DolphinLib(
        "gx",
        [
            Object(NonMatching, "revolution/gx/GXInit.c"),
            Object(NonMatching, "revolution/gx/GXFifo.c"),
            Object(NonMatching, "revolution/gx/GXAttr.c"),
            Object(NonMatching, "revolution/gx/GXMisc.c"),
            Object(NonMatching, "revolution/gx/GXGeometry.c"),
            Object(NonMatching, "revolution/gx/GXFrameBuf.c"),
            Object(NonMatching, "revolution/gx/GXLight.c"),
            Object(NonMatching, "revolution/gx/GXTexture.c"),
            # Object(NonMatching, "revolution/gx/GXBump.c", mw_version = "Wii/1.0"),
            Object(NonMatching, "revolution/gx/GXBump.c"),
            Object(NonMatching, "revolution/gx/GXTev.c"),
            Object(NonMatching, "revolution/gx/GXPixel.c"),
            Object(NonMatching, "revolution/gx/GXDisplayList.c"),
            Object(NonMatching, "revolution/gx/GXTransform.c"),
            Object(NonMatching, "revolution/gx/GXPerf.c"),
        ],
    ),
]

# Optional extra categories for progress tracking
# Adjust as desired for your project
config.progress_categories = [
    ProgressCategory("game", "Game Code"),
    ProgressCategory("sdk", "SDK Code"),
]
config.progress_each_module = args.verbose

if args.mode == "configure":
    # Write build.ninja and objdiff.json
    generate_build(config)
elif args.mode == "progress":
    # Print progress and write progress.json
    calculate_progress(config)
else:
    sys.exit("Unknown mode: " + args.mode)
