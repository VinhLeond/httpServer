#!/bin/bash
set -o xtrace
set -o errexit
set -o pipefail

echo "Input argument: --cleanBuild"
cleanBuild=$1
BUILD_PATH="build"
BASE_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

if [ $cleanBuild == 1 ]; then
    if [ -d $BUILD_PATH ]; then
        rm -rf build
    fi
fi

if [ -d $BUILD_PATH ]; then
    echo "build directory exist, proceed to do make"
    cd build
else
    echo "generate build config"
    mkdir build && cd build
    cmake ..
fi

make -j `nproc`

# Run unit_test
$BASE_DIR/$BUILD_PATH/test/unit/server_basic_test 


make install