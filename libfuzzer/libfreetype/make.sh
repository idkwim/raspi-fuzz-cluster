#!/bin/bash

set -e

CC=`which clang++-3.9`
IN="`realpath \"$1\"`"
OUT=${IN/.cc/}

if [ ! -x "${CC}" ]; then
    echo "[-] Invalid clang"
    echo '[-] Run `apt-get install clang-3.8`'
    exit 1
fi

shift
LIBS="$@"
LIBFUZZ="build/libFuzzer.a"
CPU="`grep --count processor /proc/cpuinfo`"

if [ ! -f ${LIBFUZZ} ]; then
    echo "[+] Downloading libfuzzer"
    svn co http://llvm.org/svn/llvm-project/llvm/trunk/lib/Fuzzer
    echo "[+] Building libfuzzer library"
    mkdir -p build && cd build
    ${CC} -c -g -O2 -std=c++11 ../Fuzzer/*.cpp -IFuzzer
    ar ruv libFuzzer.a Fuzzer*.o
    cd ..
fi

echo "[+] Building fuzzer"
${CC} -ggdb -O1 -fno-omit-frame-pointer -fsanitize-coverage=trace-cmp -fsanitize=undefined -fno-sanitize-recover=undefined -fsanitize-coverage=edge  -fsanitize=address ${IN} ${LIBFUZZ} ${LIBS} -o ${OUT}

echo "[+] Start a simple fuzzing run with '${OUT}'"
echo "[+] Or using your ${CPU} cores in parallel: '${OUT} -workers=${CPU} -jobs=${CPU} -timeout=3000'"
exit 0
