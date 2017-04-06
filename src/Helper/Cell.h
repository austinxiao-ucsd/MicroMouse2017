#ifndef __CELL_H__
#define __CELL_H__

/**
 * Defines a cell structure.
 * For now it indicates a pair of coordinate, will later be extended
 * to cells in maze after the flood-fill algorithm is in place.
 */
class Cell {

public:
    int y;
    int x;
    Cell(int y, int x) : y(y), x(x) {}
};
#endif