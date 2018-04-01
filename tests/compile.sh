#!/usr/bin/env sh

echo "Removing old files..."
rm -rf ./build

echo "Making dir and entering it...."
mkdir ./build && cd build

echo "Generating Cmake files...."
cmake ..

echo "Building it..."
make && cp ./bin/tsukibot tsukibot

echo "Done!"
