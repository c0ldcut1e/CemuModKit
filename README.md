# Cemu Mod Kit

Cemu Mod Kit is a development kit to make it easier to develop graphic packs for Cemu.
Cemu Mod Kit comes with a small port of [wut](https://github.com/devkitPro/wut/) called `cut`, a function patcher and an ImGui overlay.

## Compiling the graphic pack

To compile the graphic pack, `DevkitPPC` is needed.
It is recommended to use `Ninja` with the `CMakeLists.txt`.

1. Configure the project:
```
cmake -S . -B build -G Ninja
```
optionally, `DEBUG_LEVEL` can be set for the built-in `fmt` library.
The options for `DEBUG_LEVEL` are:
- OFF
- ON
- VERBOSE

by default, it is `OFF`.
To use `ON` for example, the command would be this instead:
```
cmake -S . -B build -G Ninja -DDEBUG_LEVEL=ON
```
2. Building the project
```
cmake --build build
```
This builds the `.elf` file and generates the graphic pack assembly using the `gen_patch.py` file.
Optionally, if `capstone` is installed via `pip`, the `gen_patch.py` script will generate disasembly comments in the graphic pack assembly.
