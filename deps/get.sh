#!/bin/bash

DIR=$(readlink -f $(dirname ${BASH_SOURCE[0]}))
cd $DIR

# io.js

rm -fR io.js
git clone --depth 1 https://github.com/nodejs/io.js.git

# v8cpp

rm -fR v8-cpp
bzr branch lp:v8-cpp
