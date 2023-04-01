#!/usr/bin/env bash

# check if clang++ is installed
if ! command -v clang++ &> /dev/null
then
    echo "clang++ could not be found"
    exit
fi

# build game  
echo "Compling Game"
clang++ -v --std=c++17 -fdiagnostics-color=always -Wall -g -I./dependacies/include -L./dependacies/library ./src/*.c ./src/*.cpp ./dependacies/library/libglfw.3.3.dylib -o game_app -framework OpenGl -framework Cocoa -framework IOKit -framework CoreVideo -framework CoreFoundation -Wno-deprecated

# run game
echo "Running Game, Check window"
./game_app

