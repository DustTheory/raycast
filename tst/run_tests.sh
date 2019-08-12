#!/bin/bash
echo Compiling
g++ -c Map.cpp
echo Linking
g++ Map.o -o MapTests -lsfml-graphics -lsfml-window -lsfml-system
echo Running
./MapTests
