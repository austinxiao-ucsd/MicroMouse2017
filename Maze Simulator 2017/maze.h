#ifndef __MAZE_H__
#define __MAZE_H__
#include <cmath>
#include <ctime>
#include <climits>
#include <cstdlib>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "Cell.h"
using namespace std;

const int MAZE_SIZE = 6;

class Maze{



	public: 

		Maze();
		Cell *maze[MAZE_SIZE][MAZE_SIZE];
		vector<Cell*> res;

		int manhattan_dist(int x1, int x2, int y1, int y2);

		int min4(int a, int b, int c, int d);

		void update_distances(vector<Cell*> &stack);

		void explore(vector<Cell*> &stack, int y, int x);

		//void init_maze();

		void print_maze();

		bool is_center(Cell* cell);

		void load_maze(string file_name);
		
		void print_path();

		Cell* next_move(Cell* cell);


};

#endif