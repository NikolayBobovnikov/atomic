#!/bin/sh

clear
mkdir -p build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug "-GUnix Makefiles"
make 
