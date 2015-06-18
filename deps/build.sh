#!/bin/bash

DIR=$(readlink -f $(dirname ${BASH_SOURCE[0]}))

# io.js

cd $DIR
git clone --depth 1 https://github.com/nodejs/io.js.git

cd io.js
./configure --enable-static
make -j3

# v8cpp

cd ..
bzr branch lp:v8-cpp
