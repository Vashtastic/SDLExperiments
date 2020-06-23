clear
echo OFF
echo Building and Compiling
g++ --std=c++14 -g -Wall -o myprogram.exe Test.cpp -Wall -lmingw32 -lSDL2main -lSDL2
