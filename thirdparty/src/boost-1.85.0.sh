#!/bin/sh

# Download Google Test tarball and save it with a specific filename
wget -O googletest-1.14.0.tar.gz https://github.com/google/googletest/archive/refs/tags/v1.14.0.tar.gz

# Extract the tarball
tar -xzf googletest-1.14.0.tar.gz

# Navigate into the extracted directory
cd googletest-1.14.0

# Create and navigate into the build directory
mkdir build
cd build

# Configure the project with CMake and specify the install prefix and build type
cmake -G Ninja -DCMAKE_INSTALL_PREFIX=../../../ -DCMAKE_BUILD_TYPE=Debug ..

# Build and install Google Test
ninja install

