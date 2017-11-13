#!/bin/bash
#
# Simple template for compiling target with libfuzzer. It will download and compile libFuzzer,
# then proceed to compiling your fuzzer.
#
# Syntax:
#    $ ./make myfuzzer.cc <optional-linking-flags>
#
# For better results, compile the targeted library with ASAN, for example:
#    $ ./configure CC="clang-4.0 -O2 -fno-omit-frame-pointer -g -fsanitize=address -fsanitize-coverage=trace-pc-guard,trace-cmp,trace-gep,trace-div"
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
#CC=clang++-4.0
#CC=clang++-5.0
CXX=${CC}
NCPUS="`grep --count processor /proc/cpuinfo`"
MEM_LIMIT=$((1024 / ${NCPUS}))

case ${CC} in
    clang-3.9|clang++-3.9)
        XSAN="-fsanitize=address,integer,undefined -fsanitize-coverage=edge"
        # -fsanitize-coverage=trace-pc doesn't work for some reasons on ARM...
        ;;

    clang-4.0|clang++-4.0)
        XSAN="-fsanitize=address -fsanitize-coverage=trace-pc-guard,trace-cmp,trace-gep,trace-div"
        ;;

    clang-5.0|clang++-5.0)
        XSAN="-fsanitize=fuzzer,address,integer,undefined -fsanitize-coverage=trace-pc-guard,trace-cmp,trace-gep,trace-div"
        ;;

    *)
        err "unknown clang"
        exit 1
        ;;
esac

FLAGS="-ggdb -O1 -fno-omit-frame-pointer ${XSAN}"


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
LIBFUZZ="`realpath \"../libFuzzer-$(arch).a\"`"

if [ "$1" = "clean" ]; then
    info "Cleaning stuff"
    rm -fr -- *.o ${LIBFUZZ} crash-* hang-* fuzz-*.log
    success "Done"
    exit 0
fi


shift
LIBS="$@ -lstdc++"

[ ! -f ${LIBFUZZ} ] && build_libfuzzer

info "Building '${OUT}'"
${CC} ${FLAGS} ${IN} ${LIBS} ${LIBFUZZ} -o ${OUT}

success "Success, now you can:"
echo -e "- Start a simple one-core fuzzing run by running:\n    $ ${OUT}"
if [ ${NCPUS} -gt 1 ]; then
    echo -e "- Or in parallel on ${NCPUS} cores by running:\n    $ ${OUT} -workers=${NCPUS} -jobs=${NCPUS} -timeout=3000 -rss_limit_mb=${MEM_LIMIT}"
fi
exit 0
