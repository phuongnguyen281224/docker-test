#!/bin/bash
set -e

# Create a build directory if it doesn't exist
mkdir -p build

# Navigate to the build directory
cd build

# Run CMake
cmake .. -DCMAKE_TOOLCHAIN_FILE=../toolchain.cmake

# Run make
make
