# NES Examples in C

These examples are from [Shiru's NES programming tutorial](http://shiru.untergrund.net/articles/programming_nes_games_in_c.htm).

# Building

By default the `cc65` toolset (required to build) is included as a submodule, so please clone recursively.

With the `cc65` submodule present you should be able to build as any of the following

```
# build .nes rom files for all examples
make
# build and run a specific .nes file in the default emulator
make example1
```

The original readme follows.

---

This is a set of very simple examples of programming NES software in C using cc65 compiler and my low level code library. To get more information you can check out my article on this topic: http://shiru.untergrund.net/articles/programming_nes_games_in_c.htm

How to compile: download cc65 from https://cc65.github.io/, unpack into a directory, unpack this folder into that directory (where /bin/ etc is located), run compile_all.bat


Examples:

1. outputs some text
2. moving balls using sprites
3. pad polling and nametable updating when rendering is enabled
4. metasprites, two pads polling, collision detection
5. unpacking a RLE-packed nametable created with NES Screen Tool into the VRAM
6. Controlling brightness of sprites and background.
7. Left/Right horizontal scrolling and screen splits.
8. Music/Sound effects.
9. Simple vertical scrolling a randomly generated background.
10. Vertical scrolling a level with simple collision detection.
11. Vertical scrolling a level with bouncing sprites superimposed.

mailto:shiru@mail.ru  
http://shiru.untergrund.net
