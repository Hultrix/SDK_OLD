#!/bin/sh

wget https://github.com/pocoproject/poco/archive/refs/tags/poco-1.13.3-release.tar.gz

tar -xzf poco-1.13.3-release.tar.gz

cd poco-poco-1.13.3-release

mkdir mybuild
cd mybuild

cmake -G Ninja -DBUILD_SHARED_LIBS=False -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=../../../ -DCMAKE_INSTALL_LIBDIR=lib ..

ninja install


