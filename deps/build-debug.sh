#!/bin/bash

DIR=$(readlink -f $(dirname ${BASH_SOURCE[0]}))

# node.js

cd $DIR

cd node.js
./configure --enable-static --debug
make -j3
