# Brainc
BrainF\*ck interpreter written in C for fun.

### How to compile
```bash
$ git clone --branch c --single-branch https://github.com/d-dorazio/mindblown.git brainc
$ cd brainc/
$ mkdir build/
$ cd build/
$ cmake -DCMAKE_BUILD_TYPE=Release ../
$ make
$ ./brainc ../bf/helloworld.bf
```

### How to use it

Command line interpreter:
```bash
$ ./brainc
```

File interpreter
```bash
$ ./brainc <file1> <file2>
```
