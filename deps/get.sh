#!/bin/bash

DIR=$(readlink -f $(dirname ${BASH_SOURCE[0]}))
cd $DIR

# io.js

if ! [ -d "io.js" ]; then
    git clone --depth 1 https://github.com/nodejs/io.js.git
fi

# v8cpp

if ! [ -d "v8-cpp" ]; then
    bzr branch -r4 lp:v8-cpp
fi
