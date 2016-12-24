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
using namespace std;

const int MAZE_SIZE = 16;

class Cell {

public:
    int y;
    int x;
    int dist;
    bool top_wall;
    bool right_wall;
    bool visited;

    Cell(int y, int x) : y(y), x(x), dist(0), top_wall(false), right_wall(false) {}
    Cell(int y, int x, int dist) : y(y), x(x), dist(dist), top_wall(false), right_wall(false) {}
    Cell(int y, int x, bool top_wall, bool right_wall) : y(y), x(x), top_wall(top_wall), right_wall(right_wall) {}
};

extern Cell *maze[MAZE_SIZE][MAZE_SIZE];
extern vector<Cell*> res;

int manhattan_dist(int x1, int x2, int y1, int y2);

int min4(int a, int b, int c, int d);

void update_distances(vector<Cell*> &stack);

void explore(vector<Cell*> &stack, int y, int x);

void init_maze();

void print_maze();

bool is_center(Cell* cell);

Cell* next_move(Cell* cell);

#endif