## Silmarils script unpacker

Back in the late 80's, a French company named **Silmarils** produced several video games for many 16-bit machines, using their custom framework called **ALIS**.

The games were based on a custom interpreter that would execute packed script files, which contained all the code, graphics and music used to run the game.

This tool can unpack script files targetting DOS, Amiga OCS, Amiga AGA, Atari and Falcon platforms. Macintosh is untested.

### Building

```shell
$ mkdir build && cd build
$ cmake ..
$ make
```

### Usage

```shell
$ silmarils-unpacker <input_file>
$ silmarils-unpacker <input_folder>
```