#ifndef __CELL_H__
#define __CELL_H__

class Cell {

public:
    int y;
    int x;
    int dist;
    bool top_wall;
    bool right_wall;
    bool visited;

    bool hasMouse;

    Cell(int y, int x) : y(y), x(x), dist(0), top_wall(false), right_wall(false) {}
    Cell(int y, int x, int dist) : y(y), x(x), dist(dist), top_wall(false), right_wall(false) {}
    Cell(int y, int x, bool top_wall, bool right_wall) : y(y), x(x), top_wall(top_wall), right_wall(right_wall) {}
};
#endif