## silm-depack

Back in the late 80's, a French company named **Silmarils** produced several video games for many 16-bit machines, using their custom framework called **ALIS**.

The games were based on a custom interpreter that would execute packed script files, which contained all the code, graphics and music used to run the game.

This tool can be used to depack these script files.

### Limitations

This tool has been tested with scripts files targetting Amiga, AGA, Atari and Falcon platforms. Little-endian targets (ie. x86) are not supported.

### Building
```shell
$ make
```

### Usage
```shell
$ silm-depack <input_file>
$ silm-depack <input_folder>
```
