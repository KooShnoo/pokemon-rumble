<!-- [![Build Status]][actions] ![Progress] ![DOL Progress] ![RELs Progress]  -->
Pokémon Rumble
[![Discord Badge]][discord]
=============

<!-- TODO(KooShnoo) spice this up a bit, oml i love dtk but *by god* is the example readme boring! -->

<!--
Replace with your repository's URL.
-->
<!-- [Build Status]: https://github.com/zeldaret/tww/actions/workflows/build.yml/badge.svg -->
<!-- [actions]: https://github.com/zeldaret/tww/actions/workflows/build.yml -->
<!---
Code progress URL:
https://progress.decomp.club/data/[project]/[version]/all/?mode=shield&measure=code
URL encoded then appended to: https://img.shields.io/endpoint?label=Code&url=
-->
<!-- [Progress]: https://img.shields.io/endpoint?label=Code&url=https%3A%2F%2Fprogress.decomp.club%2Fdata%2Ftww%2FGZLE01%2Fall%2F%3Fmode%3Dshield%26measure%3Dcode -->
<!---
DOL progress URL:
https://progress.decomp.club/data/[project]/[version]/dol/?mode=shield&measure=code
URL encoded then appended to: https://img.shields.io/endpoint?label=DOL&url=
-->
<!-- [DOL Progress]: https://img.shields.io/endpoint?label=DOL&url=https%3A%2F%2Fprogress.decomp.club%2Fdata%2Ftww%2FGZLE01%2Fdol%2F%3Fmode%3Dshield%26measure%3Dcode -->
<!--
REL progress URL:
https://progress.decomp.club/data/[project]/[version]/modules/?mode=shield&measure=code
URL encoded then appended to: https://img.shields.io/endpoint?label=RELs&url=
-->
<!-- [RELs Progress]: https://img.shields.io/endpoint?label=RELs&url=https%3A%2F%2Fprogress.decomp.club%2Fdata%2Ftww%2FGZLE01%2Fmodules%2F%3Fmode%3Dshield%26measure%3Dcode -->
<!--
Replace with your Discord server's ID and invite URL.
-->
[Discord Badge]: https://img.shields.io/discord/727908905392275526?color=%237289DA&logo=discord&logoColor=%23FFFFFF
[discord]: https://discord.gg/hKx3FJJgrV

Welcome to a (very) work-in-progress decompilation of the (not-so) hit game, Pokémon Rumble!
<!-- IGN rated the game as 6 out of 10, saying that it is "mindless, but fun". -->
<!-- So, instead of playing this game, come decompile it with us! -->

This repository does **not** contain any game assets or assembly whatsoever. An existing copy of the game is required.

Supported versions:

- `WPSE01_01`: Rev 0 (USA)


> [!NOTE]  
> This repo is in very early stages. Documentation is sparse. Please contact us directly with your questions at the [discord chat][discord].

What is decopmilation?
============
<!-- TODO(KooShnoo) -->
Check out [the decompilation wiki](https://wiki.decomp.dev/en/resources/decomp-intro-melee) for more information.

Dependencies
============

Windows
--------

On Windows, it's **highly recommended** to use native tooling. WSL or msys2 are **not** required.  
When running under WSL, [objdiff](#diffing) is unable to get filesystem notifications for automatic rebuilds.

- Install [Python](https://www.python.org/downloads/) and add it to `%PATH%`.
  - Also available from the [Windows Store](https://apps.microsoft.com/store/detail/python-311/9NRWMJP3717K).
- Download [ninja](https://github.com/ninja-build/ninja/releases) and add it to `%PATH%`.
  - Quick install via pip: `pip install ninja`

macOS
------

- Install [ninja](https://github.com/ninja-build/ninja/wiki/Pre-built-Ninja-packages):

  ```sh
  brew install ninja
  ```

- Install [wine-crossover](https://github.com/Gcenx/homebrew-wine):

  ```sh
  brew install --cask --no-quarantine gcenx/wine/wine-crossover
  ```

After OS upgrades, if macOS complains about `Wine Crossover.app` being unverified, you can unquarantine it using:

```sh
sudo xattr -rd com.apple.quarantine '/Applications/Wine Crossover.app'
```

Linux
------

- Install [ninja](https://github.com/ninja-build/ninja/wiki/Pre-built-Ninja-packages).
- For non-x86(_64) platforms: Install wine from your package manager.
  - For x86(_64), [wibo](https://github.com/decompals/wibo), a minimal 32-bit Windows binary wrapper, will be automatically downloaded and used.

Building
========

- Clone the repository:

  ```sh
  # todo: update this link
  git clone https://github.com/my/repo.git
  ```

<!-- TODO(KooShnoo) talk about wiiware and explain the game. maybe add more docs? -->
- Extract the game's executable: 
  - Download [encounter/decomp-toolkit](https://github.com/encounter/decomp-toolkit) (dtk) if you haven't already.
  - Use dtk to extract the game's executable
  ```sh
  dtk vfs cp PokémonRumble.wad:0000001.app:nlzss ./orig/WPSE01_01/main.dol
  ```

<!-- TODO(KooShnoo) put this in the build system -->
- Generate the pokemon csv:

  ```sh
  $ python src/pokemon_index_array_gen.py
  ```

- Configure:

  ```sh
  python configure.py
  ```

  <!-- To use a version other than `WPSE01_01` (USA), specify it with `--version`. -->
  <!-- Only USA is supported at this time. -->

- Build:

  ```sh
  ninja
  ```

Diffing
=======

Once the initial build succeeds, an `objdiff.json` should exist in the project root.

Download the latest release from [encounter/objdiff](https://github.com/encounter/objdiff). Under project settings, set `Project directory`. The configuration should be loaded automatically.

Select an object from the left sidebar to begin diffing. Changes to the project will rebuild automatically: changes to source files, headers, `configure.py`, `splits.txt` or `symbols.txt`.

![](assets/objdiff.png)
