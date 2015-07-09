#!/bin/bash

DIR=$(readlink -f $(dirname ${BASH_SOURCE[0]}))
cd $DIR

# io.js

if [ -d "io.js" ]; then
    cd io.js; git pull; cd ..
else
    git clone --depth 1 https://github.com/nodejs/io.js.git
fi

# v8cpp

if [ -d "v8-cpp" ]; then
    cd v8-cpp; cd ..
else
    bzr branch -r4 lp:v8-cpp
fi
