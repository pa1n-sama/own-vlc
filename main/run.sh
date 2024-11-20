#!/bin/bash

set -e 

BASE_NAME=$(basename *.pro .pro)

if [ ! -d "build" ]; then
    mkdir build
    cp -r cache build
fi
cd build


qmake ../*.pro
make clean
make
./"$BASE_NAME"
