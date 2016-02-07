# Compiler:
CC=g++

# General compiler flags:
C_FLAGS=-Wall -std=c++11

# Source files:
SRC=particle.cpp main.cpp 

all:
	$(CC) $(SRC) $(C_FLAGS) -o main.out

