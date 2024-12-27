#!/bin/bash

set -e 

BASE_NAME=$(basename *.pro .pro)

if [ ! -d "build" ]; then
    mkdir build
fi

if [ ! -d "$HOME/.config/VFW" ]; then
    mkdir -p $HOME/.config/VFW
    cp -r ../cache $HOME/.config/VFW
fi

cd build

qmake6 ../*.pro
make clean
make
./"$BASE_NAME"
