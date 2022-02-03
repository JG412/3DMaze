#!/bin/zsh
clear
echo "\n****************START****************\n"
g++ -g -std=c++11 milkywaymain.cpp Pathfinder.cpp -o Lab4 
./Lab4 Mazes/Solvable1.txt
echo "\n****************END****************\n"
#./check.sh