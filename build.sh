#!/usr/bin/env sh

cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
