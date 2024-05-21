#!/bin/sh

wget -O ogre-14.2.5.tar.gz https://github.com/OGRECave/ogre/archive/refs/tags/v14.2.5.tar.gz

tar -xzf ogre-14.2.5.tar.gz

cd ogre-14.2.5

mkdir build
cd build

cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../../../ -DOGRE_STATIC=ON ..

make
make install
