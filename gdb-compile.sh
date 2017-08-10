#!/usr/bin/env sh

echo "Compiling TsukiIRC...."

cmake -DCMAKE_BUILD_TYPE=Debug CMakeLists.txt

make

