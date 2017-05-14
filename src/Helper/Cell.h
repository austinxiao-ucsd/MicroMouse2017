#ifndef __CELL_H__
#define __CELL_H__

/**
 * Defines a cell structure.
 * For now it indicates a pair of coordinate, will later be extended
 * to cells in maze after the flood-fill algorithm is in place.
 */
class Cell {

public:
    int x;
    int y;
    Cell(int x, int y) : x(x), y(y) {}
};
#endif