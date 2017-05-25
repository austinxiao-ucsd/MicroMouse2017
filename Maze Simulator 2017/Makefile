# A simple makefile for CSE 100 P1

#use g++ for everything
CC= g++  	

# include debugging symbols in object files,
# and enable all warnings
CXXFLAGS= -g -Wall

#include debugging symbols in executable
LDFLAGS= -g	

bst: Maze_solver.o 
	g++ -o Maze_solver Maze_solver.o

Maze_solver.o: Maze_solver.h 

clean:
	$(RM) Maze_solver *.o