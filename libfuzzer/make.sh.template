#!/bin/bash
#
# Simple template for compiling target with libfuzzer
#
# Refs:
# - http://llvm.org/docs/LibFuzzer.html
# - https://clang.llvm.org/docs/UndefinedBehaviorSanitizer.html
# - https://clang.llvm.org/docs/SanitizerCoverage.html
#

set -e
# set -x

info()    { echo -e "\e[0;34m[*]\e[0m $*"; }
success() { echo -e "\e[0;32m[+]\e[0m $*"; }
warn()    { echo -e "\e[0;33m[!]\e[0m $*"; }
err()     { echo -e "\e[0;31m[!]\e[0m $*"; }

CC=clang++-3.9
XSAN="-fsanitize=address -fsanitize=integer -fsanitize=undefined -fno-sanitize-recover=undefined"
XSAN="${XSAN} -fsanitize-coverage=trace-cmp -fsanitize-coverage=edge"
FLAGS="-ggdb -O1 -fno-omit-frame-pointer ${XSAN}"
NCPUS="`grep --count processor /proc/cpuinfo`"
MEM_LIMIT=$((1024 / ${NCPUS}))


require_binary()
{
    bin="$1"
    which ${bin} >/dev/null 2>&1
    if [ $? -ne 0 ]; then
        err "Please install '${bin}' or check your PATH"
        exit 1
    fi
}


build_libfuzzer()
{
    info "Downloading libfuzzer"
    git clone --quiet https://chromium.googlesource.com/chromium/llvm-project/llvm/lib/Fuzzer
    info "Compiling libfuzzer"
    CXX=${CC} ./Fuzzer/build.sh >/dev/null 2>&1
    rm -fr -- Fuzzer
    success "libfuzzer built!"
}


if [ $# -lt 1 ]; then
    err "Missing argument"
    exit 1
fi


require_binary ${CC}
require_binary realpath
require_binary git

IN="`realpath \"$1\"`"
OUT=${IN/.cc/}
LIBFUZZ="`realpath \"./libFuzzer.a\"`"

if [ "$1" = "clean" ]; then
    info "Cleaning stuff"
    rm -fr -- *.o ${LIBFUZZ} crash-* hang-* fuzz-*.log
    success "Done"
    exit 0
fi


shift
LIBS="$@"

[ ! -f ${LIBFUZZ} ] && build_libfuzzer

info "Building '${OUT}'"
${CC} ${FLAGS} ${IN} ${LIBS} ${LIBFUZZ} -o ${OUT}

success "Success, now you can:"
echo -e "- Start a simple one-core fuzzing run by running \n\t $ ${OUT}"
if [ ${NCPUS} -gt 1 ]; then
    echo -e "- Or in parallel on ${NCPUS} cores by running \n\t $ ${OUT} -workers=${NCPUS} -jobs=${NCPUS} -timeout=3000 -rss_limit_mb=${MEM_LIMIT}"
fi
exit 0
