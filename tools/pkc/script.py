"""
originally posted by meme_man_not_ava <@239814414059044865> on [discord](https://discord.com/channels/759861459730956338/760220234900045824/1315907653708546118).
meme_man_not_ava says this was originally authored by "a friend of [theirs]"
"""

from script_functions import script_functions
import struct
from enum import IntEnum

class pkcOpCode(IntEnum):
    nop_0 = 0x0
    nop_1 = 0x2
    negate = 0x3
    complement = 0x4
    add = 0x5
    sub = 0x6
    multiply = 0x7
    divide = 0x8
    store = 0xA
    cmp_eq = 0xB
    cmp_neq = 0xC
    cmp_lt = 0xD
    cmp_geq = 0xE
    cmp_leq = 0xF
    cmp_gt = 0x10
    is_zero = 0x11
    bitwise_and = 0x14
    bitwise_xor = 0x15
    bitwise_or = 0x16
    bitwise_rshift = 0x17
    bitwise_lshift = 0x18
    access = 0x19
    call_imm = 0x1A
    call_ext_0 = 0x1B
    jmp_imm = 0x1C
    jmp_if_false = 0x1D
    function_epilogue = 0x1E
    pop = 0x1F
    function_prologue = 0x20
    store_ptr = 0x22
    exit = 0x23
    jmp_if_true = 0x24
    jmp_if_false_c = 0x25
    jmp_if_true_c = 0x26
    call_ext_1 = 0x28
    peek_nop = 0x36
    access_ptr = 0x3c
    push_int = 0x40
    push_s_f = 0x41
    push_str = 0x42
    push_dat = 0x43
    nop_2 = 0x4A
    switch = 0x4C


def openScript(filename):
    with open(filename, "rb") as infile:
        
        magic = infile.read(4)
        assert magic in (b"\x20\x1akp", b"pk\x1a\x20", b"PK\x1a\x20", b"\x20\x1aKP")

        flags, cod_size, dat_size, dat_count, str_size, str_count = struct.unpack(">6I", infile.read(24))
        print(f"{cod_size=:X} {dat_size=:X} {dat_count=:X}a {str_size=:X} {str_count=:X}")
        
        infile.seek(0x20)
        cod_block = infile.read(cod_size)
        dat_block = infile.read(dat_size)
        str_block = infile.read(str_size)

        print(dat_block)
        str_pool = str_block.decode('ASCII').split("\x00")
        
        if dat_count > 0:
            dat_slice = dat_size // dat_count
            dat_pool = [dat_block[x:x+dat_slice] for x in range(0, dat_size, dat_slice)]
        
        pc = 0

        infile.seek(0x20)
        while infile.peek():
            opcode = int.from_bytes(infile.read(1))
            imm = int.from_bytes(infile.read(3))
            
            print(f"{pc:04X}", end=" ")
            
            if opcode in pkcOpCode._value2member_map_:
                opcode = pkcOpCode(opcode)
                print(opcode.name, end=" ")
            else:
                print(f"{opcode=:X}", end=" ")
            
            arguments = None
            
            if opcode in (pkcOpCode.call_ext_0, pkcOpCode.call_ext_1):
                print(script_functions[imm][0], end=" ")
                arguments = (script_functions[imm][1],)
            
            elif opcode in (
                pkcOpCode.divide,
                pkcOpCode.multiply,
                pkcOpCode.add,
                pkcOpCode.sub,
                pkcOpCode.is_zero,
                pkcOpCode.pop,
                pkcOpCode.cmp_lt,
                pkcOpCode.nop_0,
                pkcOpCode.nop_1,
                pkcOpCode.nop_2,
                pkcOpCode.exit,
                pkcOpCode.negate,
                pkcOpCode.cmp_eq,
                pkcOpCode.cmp_geq,
                pkcOpCode.cmp_leq,
                pkcOpCode.cmp_gt,
                pkcOpCode.cmp_neq,
                pkcOpCode.function_epilogue,
                pkcOpCode.peek_nop
            ):
                arguments = ()
            elif opcode == pkcOpCode.push_s_f:
                arguments = (struct.unpack(">f", infile.read(4))[0],)
                pc += 1
            elif opcode == pkcOpCode.switch:
                count = imm >> 16
                arguments = (count,) + tuple(
                    f"{struct.unpack(">h", infile.read(2))[0] + pc:04X}" for _ in range(count)
                )
                if count & 1:
                    infile.read(2)
            elif opcode == pkcOpCode.function_prologue:
                val = int.from_bytes(infile.read(4))
                arguments = ((val >> 16) & 0xFF, val >> 24)
                pc += 1
            elif opcode in (
                pkcOpCode.jmp_imm,
                pkcOpCode.call_imm,
                pkcOpCode.jmp_if_false,
                pkcOpCode.jmp_if_false_c,
                pkcOpCode.push_int,
            ):
                arguments = (f"{imm:04X}",)
            
            elif opcode in (pkcOpCode.store, pkcOpCode.access, pkcOpCode.access_ptr):
                arguments = (f"0x{imm >> 16:02X}, 0x{imm & 0xFFFF:04X}",)
            
            elif opcode in (pkcOpCode.push_str,):
                arguments = (str_pool[imm],)

            elif opcode in (pkcOpCode.push_dat,):
                arguments = ([hex(x) for x in dat_pool[imm]],)

            if arguments is not None:
                print(", ".join(map(str, arguments)))
            else:
                print(f"{imm=:X}")
            
            pc += 1
            
            if opcode == pkcOpCode.exit:
                break

if "__main__" in __name__:
    import sys
    openScript(sys.argv[1])
