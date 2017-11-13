#!/bin/bash
#
# source me before compiling targeted library :)
#


COMP=clang++-3.9
# COMP=clang++-4.0
# COMP=clang++-5.0

case ${COMP} in
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

export FUZZ_CXXFLAGS="-O2 -fno-omit-frame-pointer -g ${XSAN}"
export CC="${COMP} ${FUZZ_CXXFLAGS}"
export CXX=${CC}
export CCLD=${CC}
