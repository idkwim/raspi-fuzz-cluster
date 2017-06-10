Compile sources with

```bash
$ AFL_NO_X86=1 AFL_USE_ASAN=1  CC=afl-clang-fast CXX=afl-clang-fast++ ./configure --disable-shared
$ make -j4
```
