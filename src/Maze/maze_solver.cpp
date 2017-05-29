#include "maze_solver.h"
DriveControl * driver;
int prev_mouse_dir_print = 5;
int prev_mouse_dir = NORTH;

Maze:: Maze() {
    unsigned char goal1 = MAZE_SIZE / 2;
    unsigned char goal2 = (MAZE_SIZE - 1) / 2;
    for (unsigned char i = 0; i < MAZE_SIZE; i++) {
        for (unsigned char j = 0; j < MAZE_SIZE; j++) {
            unsigned char min = min4(manhattan_dist(i, goal1, j, goal1),
                                     manhattan_dist(i, goal1, j, goal2),
                                     manhattan_dist(i, goal2, j, goal1),
                                     manhattan_dist(i, goal2, j, goal2));
            maze[i][j] = new Cell(i, j, min);
            if (i == MAZE_SIZE - 1) {
                maze[i][j]->top_wall = true;
            }
            if (j == MAZE_SIZE - 1) {
                maze[i][j]->right_wall = true;
            }
        }
    }
}

unsigned char Maze:: manhattan_dist(unsigned char x1, unsigned char x2,
                                    unsigned char y1, unsigned char y2) {

    return abs(x1 - x2) + abs(y1 - y2);
}

// Function that takes the minimum of the four given distances
unsigned char Maze:: min4(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    unsigned char min;
    (a < b) ? min = a : min = b;
    if (c < min) min = c;
    if (d < min) min = d;
    return min;
}

bool Maze:: is_center(unsigned char x, unsigned char y) {
    unsigned char goal1 =  MAZE_SIZE / 2;
    unsigned char goal2 = (MAZE_SIZE - 1) / 2;
    if (manhattan_dist(y, goal1, x, goal1) == 0 ||
            manhattan_dist(y, goal1, x, goal2) == 0 ||
            manhattan_dist(y, goal2, x, goal1) == 0 ||
            manhattan_dist(y, goal2, x, goal2) == 0) {
        return true;
    }
    return false;
}

//============================================================
unsigned char Mouse:: get_direction() {
    return direction;
}

void Mouse:: set_direction(unsigned char dir) {
    direction = dir;
}


bool Mouse:: get_front_sensor_value(){
    bool has_wall;
    if(direction == NORTH){
        if(mouse_x == MAZE_SIZE-1){ //if the mouse is at the topest row;
            return 1;
        }
        // TODO: change to check front sensor value.
        // TODO: has_wall = reference_maze->maze[mouse_x][mouse_y]->top_wall;
        has_wall = driver->has_front_wall();
        detected_maze->maze[mouse_x][mouse_y]->top_wall = has_wall;
    }
    else if(direction == SOUTH){
        if(mouse_x == 0){
            return 1;
        }
        // TODO: has_wall = reference_maze->maze[mouse_x-1][mouse_y]->top_wall; //its bottom cell's upper wall
        has_wall = driver->has_front_wall();
        detected_maze->maze[mouse_x-1][mouse_y]->top_wall = has_wall;
    }
    else if(direction == EAST){
        if(mouse_y == MAZE_SIZE-1)
            return 1;
        has_wall = driver->has_front_wall();
        detected_maze->maze[mouse_x][mouse_y]->right_wall = has_wall;
    }       
    else{ //WEST
        if(mouse_y == 0)
            return 1;
        has_wall = driver->has_front_wall();
        detected_maze->maze[mouse_x][mouse_y-1]->right_wall = has_wall;
    }
    return has_wall;
}

bool Mouse:: get_left_sensor_value(){
    bool has_wall;

    if(direction == NORTH){
        if(mouse_y == 0) //if the mouse is at the left_most column
            return 1;
        
        // TODO: has_wall = reference_maze->maze[mouse_x][mouse_y-1]->right_wall;
        has_wall = driver->has_left_wall();
        detected_maze->maze[mouse_x][mouse_y-1]->right_wall = has_wall;

    }
    else if(direction == SOUTH){
        if(mouse_y == MAZE_SIZE-1)
            return 1;

        // TODO: has_wall = reference_maze->maze[mouse_x][mouse_y]->right_wall;
        has_wall = driver->has_left_wall();
        detected_maze->maze[mouse_x][mouse_y]->right_wall = has_wall;

    }
    else if(direction == EAST){
        if(mouse_x == MAZE_SIZE-1)
            return 1;

        // TODO: has_wall = reference_maze->maze[mouse_x][mouse_y]->top_wall;
        has_wall = driver->has_left_wall();
        detected_maze->maze[mouse_x][mouse_y]->top_wall = has_wall;

    }
    else{
        if(mouse_x == 0)
            return 1;
        // TODO: has_wall = reference_maze->maze[mouse_x-1][mouse_y]->top_wall;
        has_wall = driver->has_left_wall();
        detected_maze->maze[mouse_x-1][mouse_y]->top_wall = has_wall;
    }

    return has_wall;
}

bool Mouse:: get_right_sensor_value(){

    bool has_wall;

    if(direction == NORTH){
        if(mouse_y == MAZE_SIZE-1) //if the mouse is at the right_most column
            return 1;

        // TODO: has_wall = reference_maze->maze[mouse_x][mouse_y]->right_wall;
        has_wall = driver->has_right_wall();
        detected_maze->maze[mouse_x][mouse_y]->right_wall = has_wall;

    }
    else if(direction == SOUTH){
        if(mouse_y == 0)
            return 1;

        // TODO: has_wall = reference_maze->maze[mouse_x][mouse_y-1]->right_wall;
        has_wall = driver->has_right_wall();
        detected_maze->maze[mouse_x][mouse_y-1]->right_wall = has_wall;

    }
    else if(direction == EAST){
        if(mouse_x == 0)
            return 1;

        // TODO: has_wall = reference_maze->maze[mouse_x-1][mouse_y]->top_wall;
        has_wall = driver->has_right_wall();
        detected_maze->maze[mouse_x-1][mouse_y]->top_wall = has_wall;
    }
    else{
        if(mouse_x == MAZE_SIZE-1)
            return 1;

        // TODO: has_wall = reference_maze->maze[mouse_x][mouse_y]->top_wall;
        has_wall = driver->has_right_wall();
        detected_maze->maze[mouse_x][mouse_y]->top_wall = has_wall;

    }

    return has_wall;

}


// the front sensor is 0, then the mouse can move in this direction
bool Mouse:: can_move() {
    //in the real world, instead of using 0, we need to set some constant
    //as a threshold for the sensor value;
    return (get_front_sensor_value()==0);
}


//Assumption: the maze[0][y] and maze[x][0] has left wall and bottom wall
void Mouse:: check_open_neighbor() {
    right_sensor = get_right_sensor_value();
    front_sensor = get_front_sensor_value();
    left_sensor = get_left_sensor_value();


    if(direction == NORTH) {
        if(prev == SOUTH) {
            south_open = 1;
        }

        north_open = !front_sensor;
        east_open = !right_sensor;
        west_open = !left_sensor;
    } else if(direction == SOUTH) {
        if(prev == NORTH) {
            north_open = 1;
        }

        south_open = !front_sensor;
        east_open = !left_sensor;
        west_open = !right_sensor;
    } else if(direction == EAST) {
        if(prev == WEST) {
            west_open = 1;
        }

        south_open = !right_sensor;
        east_open = !front_sensor;
        north_open = !left_sensor;
    } else { //WEST
        if(prev == EAST) {
            east_open = 1;
        }

        south_open = !left_sensor;
        west_open = !front_sensor;
        north_open = !right_sensor;
    }
  
}

unsigned char Mouse:: min_open_neighbor(vector<Cell*> cells) {
    int min = MAX;
    for (vector<Cell *>::iterator it = cells.begin(); it != cells.end(); it++) {
        if ((*it)->dist < min) {
            min = (*it)->dist;
        }
    }
    return min;
}

void Mouse:: update_distance() {
    Cell * curr;
    vector<Cell*> neighbor;
    vector<Cell*> open_neighbor;
    unsigned char min_dist;
    unsigned char x, y;
    unsigned char count = 0;
    stk.push_back(detected_maze->maze[mouse_x][mouse_y]);

    while(!stk.empty()) {
        curr = stk.back();
        stk.pop_back();
        x = curr->x;
        y = curr->y;

        if(x < MAZE_SIZE-1) { //top cell
            neighbor.push_back(detected_maze->maze[x+1][y]);
            if(!curr->top_wall) {
                open_neighbor.push_back(detected_maze->maze[x + 1][y]);
            }
        }

        if(y > 0) { //left cell
            neighbor.push_back(detected_maze->maze[x][y-1]);

            if (!(detected_maze->maze[x][y - 1]->right_wall)) {
                open_neighbor.push_back(detected_maze->maze[x][y - 1]);
            }
        }

        if(x > 0) { //bottom cell
            neighbor.push_back(detected_maze->maze[x-1][y]);
            if (!(detected_maze->maze[x-1][y]->top_wall)) {
                open_neighbor.push_back(detected_maze->maze[x-1][y]);
            }
        }

        if(y < MAZE_SIZE -1) { //right_cell
            neighbor.push_back(detected_maze->maze[x][y+1]);
            if(!curr->right_wall) {
                open_neighbor.push_back(detected_maze->maze[x][y+1]);
            }
        }
        if (open_neighbor.empty()) {
            neighbor.clear();
            continue;
        }
        min_dist = min_open_neighbor(open_neighbor);
        open_neighbor.clear();

        if (curr->dist - 1 != min_dist) {
            curr->dist = min_dist + 1;
            for (vector<Cell *>::iterator it = neighbor.begin(); it != neighbor.end(); it++) {
                if (!detected_maze->is_center((*it)->x, (*it)->y)) {
                    stk.push_back(*it);
                }
            }
            neighbor.clear();
        }
        count++;
    }
}

void Mouse::clear_stack() {
    stk.clear();
}

void Mouse:: move_one_cell() {
    check_open_neighbor();
    update_distance();
    int min_dist = MAX;
    unsigned char temp;
    if(north_open) {
        temp = detected_maze->maze[mouse_x+1][mouse_y]->dist;
        if (temp < min_dist) {
            min_dist = temp;
            direction = NORTH;
            prev = SOUTH;
        }
    }


    if(east_open) {
        temp = detected_maze->maze[mouse_x][mouse_y+1]->dist;
        if (temp < min_dist) {
            min_dist = temp;
            direction = EAST;
            prev = WEST;
        }
    }

    if(south_open) {
        temp = detected_maze->maze[mouse_x-1][mouse_y]->dist;
        if (temp < min_dist) {
            min_dist = temp;
            direction = SOUTH;
            prev = NORTH;
        }
    }
    if(west_open) {
        temp = detected_maze->maze[mouse_x][mouse_y-1]->dist;
        if (temp < min_dist) {
            min_dist = temp;
            direction = WEST;
            prev = EAST;
        }
    }
    //Move
    if(direction == NORTH) {
        mouse_x += 1;
    } else if(direction == SOUTH) {
        mouse_x -= 1;
    } else if (direction == EAST) {
        mouse_y += 1;
    } else { //WEST
        mouse_y -= 1;
    }
    north_open = south_open = east_open = west_open = 0;
}

bool Mouse::center_found() {
    return detected_maze->is_center(mouse_x, mouse_y);
}

int Mouse::get_next_cell_direction() {
    return direction;    
}

int Mouse::get_prev_direction() {
    return prev_mouse_dir_print;
}

int Mouse:: solve_maze() {
    const unsigned char STRAIGHT = 0, LEFT = 1, RIGHT = 2, UTURN = 3;
    
    prev_mouse_dir_print = prev_mouse_dir;
    
  //  

    //while the mouse has not find the center of the Maze
    move_one_cell();
    unsigned char state = 5;
    
    
    if (prev_mouse_dir == direction) {
        if (prev_mouse_dir == NORTH && direction == NORTH) {
            can_reset_mouse = true;
        }
        state = STRAIGHT;
    }
    // Mouse is facing south
    else if (prev_mouse_dir == SOUTH && direction == NORTH) {
        state = UTURN;
        prev_mouse_dir = NORTH;
    } else if (prev_mouse_dir == SOUTH && direction == EAST) {
        state = LEFT;
        prev_mouse_dir = EAST;
    } else if (prev_mouse_dir == SOUTH && direction == WEST) {
        state = RIGHT;
        prev_mouse_dir = WEST;
    }
    // Mouse is facing north
    else if (prev_mouse_dir == NORTH && direction == EAST) {
        state = RIGHT;
        prev_mouse_dir = EAST;
    } else if (prev_mouse_dir == NORTH && direction == WEST) {
        state = LEFT;
        prev_mouse_dir = WEST;
    } else if (prev_mouse_dir == NORTH && direction == SOUTH) {
        state = UTURN;
        prev_mouse_dir = SOUTH;
    }
    // Mouse is facing west
    else if (prev_mouse_dir == WEST && direction == NORTH) {
        state = RIGHT;
        prev_mouse_dir = NORTH;
    } else if (prev_mouse_dir == WEST && direction == SOUTH) {
        state = LEFT;
        prev_mouse_dir = SOUTH;
    } else if (prev_mouse_dir == WEST && direction == EAST) {
        state = UTURN;
        prev_mouse_dir = EAST;
    }
    // Mouse is facing west
    else if (prev_mouse_dir == EAST && direction == NORTH) {
        state = LEFT;
        prev_mouse_dir = NORTH;
    } else if (prev_mouse_dir == EAST && direction == SOUTH) {
        state = RIGHT;
        prev_mouse_dir = SOUTH;
    } else if (prev_mouse_dir == EAST && direction == WEST) {
        state = UTURN;
        prev_mouse_dir = WEST;
    }

    
    return state;
}



Mouse:: Mouse(DriveControl * prev_driver) {
    can_reset_mouse = false;
    driver = prev_driver;
    detected_maze = new Maze();
    prev = (unsigned char) 5;
    direction = NORTH;
    mouse_x = mouse_y = 0;
    north_open = south_open = east_open = west_open = 0;
}