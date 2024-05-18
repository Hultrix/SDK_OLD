#!/bin/sh

wget -O yoga-3.0.4.tar.gz  https://github.com/facebook/yoga/archive/refs/tags/v3.0.4.tar.gz

tar -xzf yoga-3.0.4.tar.gz

cd yoga-3.0.4

mkdir build
cd build

cmake -G Ninja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=../../../ -DCMAKE_INSTALL_LIBDIR=lib ..

ninja install
