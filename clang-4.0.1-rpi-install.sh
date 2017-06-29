#!/bin/bash

set -e

url="http://releases.llvm.org/4.0.1/clang+llvm-4.0.1-armv7a-linux-gnueabihf.tar.xz"
prefix="$(basename ${url/.tar.xz/})"

pushd .
cd /tmp
wget ${url}
sudo tar -C /usr -xpvJf ${prefix}.tar.xz --transform="flags=r;s!${prefix}!!"
rm ${prefix}.tar.xz
popd

exit 0
