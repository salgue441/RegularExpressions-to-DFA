#!/bin/bash

# Build the project using CMake
mkdir -p build
cd build
cmake ..
cmake --build .

# Run the Regular Expression to DFA Converter
./regex-to-dfa-converter
