#!/bin/sh

wget https://boostorg.jfrog.io/artifactory/main/release/1.85.0/source/boost_1_85_0_rc3.tar.gz

tar -xzf boost_1_85_0_rc3.tar.gz

cd boost_1_85_0

./bootstrap.sh --prefix=../../

./b2 link=static install
