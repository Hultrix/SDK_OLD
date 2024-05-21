#!/bin/bash

git clone 'https://chromium.googlesource.com/chromium/tools/depot_tools.git'
export PATH="${PWD}/depot_tools:${PATH}"

# Download the packages
wget https://github.com/google/skia/archive/refs/tags/canvaskit/0.34.0.tar.gz

tar -xvf 0.34.0.tar.gz

# Change directory to the glibc directory
cd skia-canvaskit-0.34.0

python3 tools/git-sync-deps

# Run configure with the adjusted paths
./bin/gn gen 'out/Static' --args='
    is_official_build=true 
    is_component_build=false
    skia_enable_tools=false
    target_os="linux" 
    target_cpu="x64"
    skia_use_icu=false 
    skia_use_sfntly=false 
    skia_use_piex=true
    skia_use_system_expat=false 
    skia_use_system_freetype2=false 
    skia_use_system_libjpeg_turbo=false 
    skia_use_system_libpng=false 
    skia_use_system_libwebp=false 
    skia_use_system_zlib=false
    skia_enable_gpu=true'

ninja -C out/Static


