#!/bin/bash

# Build the project using CMake
cmake --build build --target regex-to-dfa-converter

# Navigate to the build directory
cd build

# Run the tests using CTest
ctest -R test_regex-to-dfa-converter
