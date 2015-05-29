# Braincpp

Simple Brain\*ck interpreter written in C++11.

# How to build
```bash
$ git clone --branch cpp --single-branch https://github.com/d-dorazio/mindblown.git braincpp
$ cd braincpp/
$ mkdir build/
$ cd build/
$ cmake -DCMAKE_BUILD_TYPE=RELEASE ../
$ make
$ ./braincpp ../bf/helloworld.bf
```

# How to use
Command line interpreter:
```bash
$ ./braincpp
```

File interpreter:
```bash
$ ./braincpp ../bf/helloworld.bf ../bf/life.bf
```
