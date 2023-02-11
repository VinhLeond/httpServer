#!/bin/bash
echo "Input argument: --cleanBuild"
cleanBuild=$1

if [ $cleanBuild == 1 ]; then
    if [ -d "build" ]; then
        rm -rf build
    fi
fi

if [ -d "build" ]; then
    echo "build directory exist, proceed to do make"
    cd build
else
    echo "generate build config"
    mkdir build && cd build
    cmake ..
fi

make -j `nproc`