#!/bin/sh

wget -O dlib-19.24.4.tar.gz https://github.com/davisking/dlib/archive/refs/tags/v19.24.4.tar.gz

tar -xzf dlib-19.24.4.tar.gz

cd dlib-19.24.4

#mkdir build
#cd build

#cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=../../../ -DLEXBOR_BUILD_SHARED=OFF -DCMAKE_INSTALL_LIBDIR=lib ..
#make
#make install
