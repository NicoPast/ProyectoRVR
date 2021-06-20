#!/bin/bash

cd PongArkanoid/build;

cmake -DCMAKE_BUILD_TYPE=Debug ../;

cmake --build . -- -j 4;