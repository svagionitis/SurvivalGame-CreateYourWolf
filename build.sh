#!/bin/bash
# Script for out of source build.

BUILD_DIR="build-$(uname -m)"

mkdir -p ${BUILD_DIR}

cd ${BUILD_DIR}

cmake ../
make

cd -
