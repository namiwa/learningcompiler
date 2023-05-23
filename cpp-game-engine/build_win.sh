#!/usr/bin/env bash

# check if clang++ is installed
if ! command -v g++ &> /dev/null
then
    echo "g++ could not be found"
    exit
fi

if [[ -x "game_app" ]]
then
    echo "Previous game build exists, deleting..."
    rm ./game_app
fi

# build game  
echo "Compling Game"
g++ -v --std=c++17 -fdiagnostics-color=always -Wall -g -I./dependacies/include -L./dependacies/library ./src/*.c ./src/*.cpp ./dependacies/library/libglfw.3.3.dylib -o game_app -lOpenGL -Wno-deprecated

# run game
echo "Running Game, Check window"
./game_app

