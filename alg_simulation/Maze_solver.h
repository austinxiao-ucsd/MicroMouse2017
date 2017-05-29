#include <string>
#include <vector>
#include <iostream>
#include <fstream>

const unsigned char MAZE_SIZE = 16;
const unsigned char NORTH = 0;
const unsigned char SOUTH = 1;
const unsigned char WEST = 2;
const unsigned char EAST = 3;
const int MAX = 256;

using namespace std;

class Cell {
public:
    unsigned char x, y;
    unsigned char dist;
    bool top_wall, right_wall;
    Cell(unsigned char x, unsigned char y, unsigned char dist) :
        x(x), y(y), dist(dist) {
        top_wall = right_wall = false;
    }
    Cell(unsigned char x, unsigned char y, bool top_wall, bool right_wall)
        : x(x), y(y), top_wall(top_wall), right_wall(right_wall) {}
};

class Maze {
public:
    Maze();

    ~Maze() {};

    unsigned char manhattan_dist(unsigned char x1, unsigned char x2, unsigned char y1, unsigned char y2);

    unsigned char min4(unsigned char a, unsigned char b, unsigned char c, unsigned char d);

    bool is_center(unsigned char x, unsigned char y);

    void print_maze(int x, int y, int dir);

    void print_maze();

    void print_mouse(int dir);

    void move();

    void load_maze(string file_name);

    Cell * maze[MAZE_SIZE][MAZE_SIZE];
};

class Mouse {
public:
    unsigned char direction, next_cell_dir, prev_mouse_dir;
    //the current position of Mouse, should be identical to the Cell'x and y
    unsigned char mouse_x,  mouse_y;
    // the previous direction, the previous direction is open by default
    unsigned char prev;
    bool north_open, south_open, east_open, west_open;
    bool front_sensor, left_sensor, right_sensor;
    Maze * reference_maze;
    Maze * detected_maze;
    std::vector <Cell*> stk; //vc was used as a stack to update the distance

    Mouse();

    ~Mouse() {
        for (int i = 0; i < MAZE_SIZE; i++) {
            // delete [] *maze[i];
            for (int j = 0; j < MAZE_SIZE; j++) {
                delete detected_maze->maze[i][j];
            }
        }
        delete detected_maze;
    };

    void set_direction(unsigned char dir);

    unsigned char get_direction();

    void print_sensor_reading();

    void print_open_direction();

    void print_maze();

    bool get_front_sensor_value(); //read the value from the front sensor and will update the wall properly

    bool get_left_sensor_value(); //read the value from the left sensor and will update the wall properly

    bool get_right_sensor_value(); //read the value from the right sensor and will update the wall properly

    void test_sensor();

    bool can_move();

    void update_distance();

    unsigned char min_open_neighbor(vector<Cell*> cells);

    void check_open_neighbor();

    void solve_maze();

    void move_one_cell();

    void load_maze(string file_name);

    void print_reference_maze();

};
