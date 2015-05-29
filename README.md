BraiHask
===========
It's a BrainF\*ck interpreter written with the only goal of gaining experience with Haskell. It can also translate BrainF\*uck programs to C code. You can get useful informations on what the interpreter does using --help or -h options.


How To Build
==============
Build using a [cabal-sandbox](https://www.haskell.org/cabal/users-guide/installing-packages.html#developing-with-sandboxes)(recommended)
```
$ git clone --branch haskell --single-branch https://github.com/d-dorazio/mindblown.git haskell
$ cd BraiHask/
$ cabal sandbox init
$ cabal install --only-dependencies
$ cabal build
```
The binary will be located in the ./dist/build/BrainHask/ directory.

How To Use
==============
Command line interpreter(quit typing `quit`):
```
$ ./dist/build/BrainHask/BrainHask 
```

File interpreter:
```
$ ./dist/build/BrainHask/ ./bf/helloworld.bf ./bf/helloworld.bf
```

BrainF*ck program to C code:
```
$ ./dist/build/BrainHask/ --toC . ./bf/helloworld.bf
```
The option `--toC` requires the directory where to store C files.

