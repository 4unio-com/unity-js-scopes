#!/bin/bash

DIR=$(readlink -f $(dirname ${BASH_SOURCE[0]}))
cd $DIR

# node.js

if [ -d "node.js" ]; then
    cd node.js; cd ..
else
    bzr branch http://bazaar.launchpad.net/~webapps/unity-js-scopes/node.js node.js
fi

# v8cpp

if [ -d "v8-cpp" ]; then
    cd v8-cpp; cd ..
else
    bzr branch http://bazaar.launchpad.net/~unity-team/v8-cpp/trunk v8-cpp
fi
