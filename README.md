# raspi-fuzz-cluster

Transform your Raspberry-Pi cluster into a fuzzing farm

![](http://i.imgur.com/o0kyt5f.jpg)

A bunch of scripts and config tools for building and managing my Raspberry-Pi
fuzzing cluster.

Based on Raspbian distro.

Fuzzers:

  - [libFuzzer](http://llvm.org/docs/LibFuzzer.html)
  - [AFL](http://lcamtuf.coredump.cx/afl)


## clang-3.9 (from APT)

Needs (at least) the following DEB packages:
```bash
sudo apt-get install clang-3.9 llvm-3.9 cmake automake pkg-config autoconf m4 gdb
```

## clang-5.x (from llvm.org)

```bash
sh clang-rpi-install.sh
```
