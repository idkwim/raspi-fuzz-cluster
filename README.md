# raspi-fuzz-cluster

A bunch of scripts and config tools for building and managing my Raspberry-Pi
fuzzing cluster.

Based on Raspbian distro.

Fuzzers:

  - [libFuzzer](http://llvm.org/docs/LibFuzzer.html)
  - [AFL](http://lcamtuf.coredump.cx/afl)


Needs (at least) the following DEB packages:

```
apt-get install clang-3.9 llvm-3.9 cmake automake pkg-config autoconf m4 gdb
```
