#include "mbed.h"
#include <vector>

const int MAZE_SIZE = 16;
const int NORTH = 0;
const int SOUTH = 1;
const int WEST = 2; 
const int EAST = 3;
const int MAX = 256;

//Mouse's left, right, and top wall is different from Maze's right wall and top wall
//All the wall detected by the mouse is based on it's sensor positions. 
class Cell {

public:
    int y;
    int x;
    int dist;
    bool top_wall;
    bool right_wall;
    bool visited;
    bool hasMouse;

    Cell(int x, int y) : y(y), x(x), dist(0), top_wall(false), right_wall(false), hasMouse(false){}
    Cell(int x, int y, int dist) : y(y), x(x), dist(dist), top_wall(false), right_wall(false), hasMouse(false){}
    Cell(int x, int y, bool top_wall, bool right_wall) : y(y), x(x), top_wall(top_wall), right_wall(right_wall), hasMouse(false){}
};

class Maze{

    public: 

        Maze();

        ~Maze();

        int manhattan_dist(int x1, int x2, int y1, int y2);

        int min4(int a, int b, int c, int d);

        //int min_open_neighbor(vector<Cell*> cells);

        //void update_distances(vector<Cell*> &stack);

        bool is_center(Cell* cell);

        bool is_center(int x, int y);

        void print_maze(int x, int y, int dir);

        void print_maze();

        void print_mouse(int dir);

        void move();
        
        

        //void explore(vector<Cell*> &stack, int y, int x);

        
        //Cell* next_move(Cell* cell);

        //void print_path();

        Cell * maze[MAZE_SIZE][MAZE_SIZE];
        
        vector<Cell*> res;
};

class Mouse{
    

    public:
        int direction; //initial direction is north

        //the current position of Mouse, should be identical to the Cell'x and y
        int mouse_x;
        int mouse_y;

        //Those four variable indicates if the mouse can move in the certain direction
        bool north_open;
        bool south_open;
        bool east_open;
        bool west_open;

        bool front_sensor;
        bool left_sensor;
        bool right_sensor;

        int prev; // the previous direction, the previous direction is open by default

        Maze * reference_maze;
        Maze * detected_maze;

        std::vector <Cell*> stk; //vc was used as a stack to update the distance
        
        Mouse();
        ~Mouse();
        
        void set_direction(int dir);
        
        int get_direction();

        void print_sensor_reading();

        void print_open_direction();

        void print_maze();
        
        bool get_front_sensor_value(); //read the value from the front sensor and will update the wall properly

        bool get_left_sensor_value(); //read the value from the left sensor and will update the wall properly

        bool get_right_sensor_value(); //read the value from the right sensor and will update the wall properly
        
        void test_sensor();

        bool can_move();

        void update_distance();

        int min_open_neighbor(vector<Cell*> cells);

        void check_open_neighbor();

        int solve_maze();

        int move_one_cell();

        bool center_reached();

        void print_reference_maze();

};