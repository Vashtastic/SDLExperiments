cls
ECHO OFF
ECHO Building and Compiling
g++ --std=c++17 -ggdb -o KeyLogger.exe SimpleKeyLogger.cpp -lmingw32 -lSDL2main -lSDL2