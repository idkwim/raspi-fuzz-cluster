#!/bin/bash

set -e

# llvm + clang 4.0.1
url="http://releases.llvm.org/4.0.1/clang+llvm-4.0.1-armv7a-linux-gnueabihf.tar.xz"
clang="/usr/bin/clang-4.0"
clangpp="/usr/bin/clang++-4.0"

# llvm + clang 5.0.0
url="http://releases.llvm.org/5.0.0/clang+llvm-5.0.0-armv7a-linux-gnueabihf.tar.xz"
clang="/usr/bin/clang-5.0"
clangpp="/usr/bin/clang++-5.0"


prefix="$(basename ${url/.tar.xz/})"

pushd .
cd /tmp
wget ${url}
sudo tar -C /usr -xpvJf ${prefix}.tar.xz --transform="s!${prefix}!!"
sudo ln -sf ${clang} ${clangpp}
rm ${prefix}.tar.xz
popd

exit 0
