#!/bin/sh

rm -fr build
mkdir -p build
cd build
cmake ..
make
rm -fr build
