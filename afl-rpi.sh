#!/bin/bash
#
# Automated installation of latest AFL for Raspberry-Pi (ARM)
#
#

set -e

download_afl()
{
    cd ${HOME}
    rm -fr -- afl-*
    curl -fSsL http://lcamtuf.coredump.cx/afl.tgz | tar xz
    export afl_dir="$(find . -type d -iname "afl-*"|sort|tail -1)"
    export afl_dir="$(realpath ${afl_dir})"
}

install_afl()
{
    d="$1"
    cd ${d}
    export CC=clang-3.9
    export CXX=clang++-3.9
    export AFL_NO_X86=1
    [ -r /usr/bin/llvm-config ] || sudo ln -sf /usr/bin/llvm-config-3.9 /usr/bin/llvm-config
    make -j4
    make -j4 -C llvm_mode
    sudo AFL_NO_X86=1 make install
}

linking_afl()
{
    sudo rm -f /usr/local/bin/afl-clang
    sudo rm -f /usr/local/bin/afl-clang++
    sudo ln -s /usr/local/bin/afl-clang-fast /usr/local/bin/afl-clang
    sudo ln -s /usr/local/bin/afl-clang-fast++ /usr/local/bin/afl-clang++
    ln -sf $1 ${HOME}/afl-latest
}

pushd .

echo "[+] Downloading AFL"
download_afl ${afl_dir}

echo "[+] Installing AFL -> ${afl_dir}"
install_afl ${afl_dir}

echo "[+] Linking AFL"
linking_afl ${afl_dir}

echo "[!] Success"
unset afl_dir

popd
