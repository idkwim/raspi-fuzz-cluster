#!/bin/bash
#
# source this file
#

export FUZZ_CXXFLAGS="-O2 -fno-omit-frame-pointer -g -fsanitize=address,undefined -fsanitize-coverage=trace-pc-guard"
export CC="clang-4.0 ${FUZZ_CXXFLAGS}"
export CXX=${CC}
export CCLD=${CC}
