#!/usr/bin/env bash

# check if clang++ is installed
if ! command -v clang++ &> /dev/null
then
    echo "clang++ could not be found"
    exit
fi

if [[ $1 == "game_app" ]]
then
    echo "Previous game build exists, deleting..."
    rm ./game_app
    rm -rf game_app.dSYM/
fi

# build game  
echo "Compling Game"
clang++ -v --std=c++17 -fdiagnostics-color=always -Wall -ggdb -I./dependacies/include -L./dependacies/library ./src/*.c ./src/*.cpp -lstdc++fs ./dependacies/library/libglfw.3.3.dylib -o game_app -framework OpenGl -framework Cocoa -framework IOKit -framework CoreVideo -framework CoreFoundation -Wno-deprecated

run_game ()
{
    if [[ "$1" == "valgrind" ]]
    then
        echo "Running Game with Valgrind, Check Window"
        valgrind -q ./game_app
        exit 
    fi
    echo "Running Game, Check window"
    ./game_app
    exit
}

if [[ $2 == "valgrind" ]] 
then
    if ! command -v valgrind &> /dev/null
    then
        echo "valgrind could not be found"
        exit
    fi
    run_game "valgrind"
fi

run_game

