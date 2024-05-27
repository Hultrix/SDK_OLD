#!/bin/sh

wget -O lexbor-2.3.0.tar.gz https://github.com/lexbor/lexbor/archive/refs/tags/v2.3.0.tar.gz

tar -xzf lexbor-2.3.0.tar.gz

cd lexbor-2.3.0

mkdir build
cd build

cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=../../../ -DLEXBOR_BUILD_SHARED=OFF -DCMAKE_INSTALL_LIBDIR=lib ..
make
make install
