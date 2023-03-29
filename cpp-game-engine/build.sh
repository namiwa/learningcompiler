#!/usr/bin/env bash

# check if clang++ is installed
if ! command -v clang++ &> /dev/null
then
    echo "clang++ could not be found"
    exit
fi

# helpers

# Function to execute commands
exe() { echo "\$ $@" ; "$@"; }

clang++ --std=c++17 -fdiagnostics-color=always -Wall -g -I/dependacies/include -L/dependacies/library *.cpp ./dependacies/library/libglfw.3.3.dylib -o game_app -framework OpenGl -framework Cocoa -framework IOKit -framework CoreVideo -framework CoreFoundation -Wno-deprecated
game_app

