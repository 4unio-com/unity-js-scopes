#!/bin/bash

DIR=$(readlink -f $(dirname ${BASH_SOURCE[0]}))

# io.js

cd $DIR

cd io.js
./configure
make -j3
