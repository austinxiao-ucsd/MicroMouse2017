#include "Maze_solver.h"

//==============================================================
Maze:: Maze(){
	int goal1 = MAZE_SIZE / 2;
    int goal2 = (MAZE_SIZE - 1) / 2;
    for (int i = 0; i < MAZE_SIZE; i++) {
        for (int j = 0; j < MAZE_SIZE; j++) {
        // Distance of the cell will be the minimum distance to the closest
        // one out of four middle destination cells.

            int min = min4(manhattan_dist(i, goal1, j, goal1),
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

int Maze:: manhattan_dist(int x1, int x2, int y1, int y2) {
    
    return abs(x1 - x2) + abs(y1 - y2);
}


// Function that takes the minimum of the four given distances

int Maze:: min4(int a, int b, int c, int d) {
    int min;
    (a < b) ? min = a : min = b;
    if (c < min) min = c;
    if (d < min) min = d;
    return min;
}

void Maze:: load_maze(string file_name) {
    ifstream file(file_name);
    string top, right;
    int row = MAZE_SIZE - 1;
    while (row >= 0) {
        getline(file, top);
        getline(file, right);
        for (int col = 0; col < MAZE_SIZE; col++) {
            maze[row][col] = new Cell(row, col, top[(col * 2) + 1] == '-', right[(col * 2) + 2] == '|');
        }
        row--;
    }

    int goal1 = MAZE_SIZE / 2;
    int goal2 = (MAZE_SIZE - 1) / 2;
    int s = 0;

    for (int i = 0; i < MAZE_SIZE; i++) {
        for (int j = 0; j < MAZE_SIZE; j++) {
            // Distance of the cell will be the minimum distance to the closest
            // one out of four middle destination cells.
            maze[i][j]->dist = min4(manhattan_dist(i, goal1, j, goal1),
                                    manhattan_dist(i, goal1, j, goal2),
                                    manhattan_dist(i, goal2, j, goal1),
                                    manhattan_dist(i, goal2, j, goal2));
        }
    }
}

void Maze:: print_maze(){
    // print top wall
    for (int i = 0; i < MAZE_SIZE; i++) {
        cout << "+---";
    }
    cout << "+";

    printf("   ");
    
    for (int i = 0; i < MAZE_SIZE; i++) {
        cout << "+---";
    }
    cout << "+\n";

    int rows = MAZE_SIZE + (MAZE_SIZE - 1);
    int y;

    //first go through rows
    for (int i = 0; i < rows; i++) {
        if (i % 2 == 0) {
            y = MAZE_SIZE - 1 - i / 2;
        }
        else {
            y = MAZE_SIZE - 1 - (i / 2 + 1);
        }
        for (int j = 0; j < MAZE_SIZE; j++) {

            if (i % 2 != 0) {
                if (maze[y][j]->top_wall) {
                    printf("+---");
                }
                else {
                    printf("+   ");
                }
                if (j == MAZE_SIZE - 1) {
                    printf("+");
                }
            }

            else {
                if (j == 0) {
                    printf("|");
                }

                int dist = maze[y][j]->dist;

                if (dist > 99) {
                    printf("%d", dist);
                }
                else if (dist > 9) {
                    printf(" %d", dist);
                }
                else {
                    printf(" %d ", dist);
                }

                if (maze[y][j]->right_wall || j == MAZE_SIZE - 1) {
                    printf("|");
                }
                else {
                    printf(" ");
                }
            }
        }

        printf("   ");

        for (int j = 0; j < MAZE_SIZE; j++) {

            if (i % 2 != 0) {
                if (maze[y][j]->top_wall) {
                    printf("+---");
                }
                else {
                    printf("+   ");
                }
                if (j == MAZE_SIZE - 1) {
                    printf("+");
                }
            }

            else {
                if (j == 0) {
                    printf("|");
                }

               	printf("   ");

                if (maze[y][j]->right_wall || j == MAZE_SIZE - 1) {
                    printf("|");
                }
                else {
                    printf(" ");
                }
            }
        }
        printf("\n");
    }
        //print the bottom
    for (int i = 0; i < MAZE_SIZE; i++) {
        printf("+---");
    }
    cout << "+";

    printf("   ");

    for (int i = 0; i < MAZE_SIZE; i++) {
        cout << "+---";
    }

    printf("+\n\n");
}


//This method will print Mouse position in the Maze
void Maze:: print_maze(int mouse_x, int mouse_y, int dir){

	bool hasMouse; 

	if(mouse_x < 0 || mouse_y < 0){
		hasMouse = false;
	}


	    // print top wall
    for (int i = 0; i < MAZE_SIZE; i++) {
        cout << "+---";
    }
    cout << "+";

    printf("   ");
    
    for (int i = 0; i < MAZE_SIZE; i++) {
        cout << "+---";
    }
    cout << "+\n";

    int rows = MAZE_SIZE + (MAZE_SIZE - 1);
    int y;

    //first go through rows
    for (int i = 0; i < rows; i++) {
        if (i % 2 == 0) {
            y = MAZE_SIZE - 1 - i / 2;
        }
        else {
            y = MAZE_SIZE - 1 - (i / 2 + 1);
        }
        for (int j = 0; j < MAZE_SIZE; j++) {

            if (i % 2 != 0) {
                if (maze[y][j]->top_wall) {
                    printf("+---");
                }
                else {
                    printf("+   ");
                }
                if (j == MAZE_SIZE - 1) {
                    printf("+");
                }
            }

            else {
                if (j == 0) {
                    printf("|");
                }

                int dist = maze[y][j]->dist;

                if (dist > 99) {
                    printf("%d", dist);
                }
                else if (dist > 9) {
                    printf(" %d", dist);
                }
                else {
                    printf(" %d ", dist);
                }

                if (maze[y][j]->right_wall || j == MAZE_SIZE - 1) {
                    printf("|");
                }
                else {
                    printf(" ");
                }
            }
        }

        printf("   ");

        for (int j = 0; j < MAZE_SIZE; j++) {

            if (i % 2 != 0) {
                if (maze[y][j]->top_wall) {
                    printf("+---");
                }
                else {
                    printf("+   ");
                }
                if (j == MAZE_SIZE - 1) {
                    printf("+");
                }
            }

            else {
                if (j == 0) {
                    printf("|");
                }

                if(hasMouse && y == mouse_x && j == mouse_y){
                	print_mouse(dir);
                } 
                else{
               		printf("   ");
                }

                if (maze[y][j]->right_wall || j == MAZE_SIZE - 1) {
                    printf("|");
                }
                else {
                    printf(" ");
                }
            }
        }
        printf("\n");
    }
        //print the bottom
    for (int i = 0; i < MAZE_SIZE; i++) {
        printf("+---");
    }
    cout << "+";

    printf("   ");

    for (int i = 0; i < MAZE_SIZE; i++) {
        cout << "+---";
    }

    printf("+\n\n");

}


void Maze:: print_mouse(int dir){
	if(dir == NORTH){
		printf(" ^ ");
	}
	else if(dir == SOUTH){
		printf(" V ");
	}
	else if(dir == WEST){
		printf(" < ");
	}
	else{
		printf(" > "); //EAST
	}
}

bool Maze:: is_center(Cell *cell) {
    int x = cell->x;
    int y = cell->y;
    int goal1 = MAZE_SIZE / 2;
    int goal2 = (MAZE_SIZE - 1) / 2;
    if (manhattan_dist(y, goal1, x, goal1) == 0 ||
        manhattan_dist(y, goal1, x, goal2) == 0 ||
        manhattan_dist(y, goal2, x, goal1) == 0 ||
        manhattan_dist(y, goal2, x, goal2) == 0) {
        return true;
    }
    return false;
}

bool Maze:: is_center(int x, int y) {
    int goal1 = MAZE_SIZE / 2;
    int goal2 = (MAZE_SIZE - 1) / 2;
    if (manhattan_dist(y, goal1, x, goal1) == 0 ||
        manhattan_dist(y, goal1, x, goal2) == 0 ||
        manhattan_dist(y, goal2, x, goal1) == 0 ||
        manhattan_dist(y, goal2, x, goal2) == 0) {
        return true;
    }
    return false;
}

//============================================================
int Mouse:: get_direction(){
    return direction;
}

void Mouse:: set_direction(int dir){
    direction = dir;
}

void Mouse:: load_maze(string file_name){
	reference_maze->load_maze(file_name);
}

void Mouse:: print_reference_maze(){
	reference_maze->print_maze(); 
}

void Mouse:: print_maze(){
	detected_maze->print_maze(mouse_x, mouse_y, direction);
}


bool Mouse:: get_front_sensor_value(){
	if(direction == NORTH){
		if(mouse_x == MAZE_SIZE-1){ //if the mouse is at the topest row;
			return 1;
		}
		return reference_maze->maze[mouse_x][mouse_y]->top_wall;
	}
	else if(direction == SOUTH){
		if(mouse_x == 0){
			return 1;
		}
		return reference_maze->maze[mouse_x-1][mouse_y]->top_wall; //its bottom cell's upper wall

	}
	else if(direction == EAST){
		if(mouse_y == MAZE_SIZE-1)
			return 1;
		return reference_maze->maze[mouse_x][mouse_y]->right_wall;
	}		
	else{ //WEST
		if(mouse_y == 0)
	 		return 1;
		return reference_maze->maze[mouse_x][mouse_y-1]->right_wall;

	}
}

bool Mouse:: get_left_sensor_value(){
	if(direction == NORTH){
		if(mouse_y == 0) //if the mouse is at the left_most column
			return 1;
		return reference_maze->maze[mouse_x][mouse_y-1]->right_wall;
	}
	else if(direction == SOUTH){
		if(mouse_y == MAZE_SIZE-1)
			return 1;
		return reference_maze->maze[mouse_x][mouse_y]->right_wall;

	}
	else if(direction == EAST){
		if(mouse_x == MAZE_SIZE-1)
			return 1;
		return reference_maze->maze[mouse_x][mouse_y]->top_wall;

	}
	else{
		if(mouse_x == 0)
			return 1;
		return reference_maze->maze[mouse_x-1][mouse_y]->top_wall;
	}
}




bool Mouse:: get_right_sensor_value(){
	if(direction == NORTH){
		if(mouse_y == MAZE_SIZE-1){ //if the mouse is at the right_most column
			return 1;
		}
		return reference_maze->maze[mouse_x][mouse_y]->right_wall;
	}
	else if(direction == SOUTH){
		if(mouse_y == 0)
			return 1;
		return reference_maze->maze[mouse_x][mouse_y-1]->right_wall;

	}
	else if(direction == EAST){
		if(mouse_x == 0)
			return 1;
		return reference_maze->maze[mouse_x-1][mouse_y]->top_wall;
	}
	else{
		if(mouse_x == MAZE_SIZE-1)
			return 1;
		return reference_maze->maze[mouse_x][mouse_y]->top_wall;

	}

}

void Mouse:: test_sensor(){
    mouse_x = 1;
    mouse_y = 1;
    direction = EAST;

    print_maze();
    printf("right sensor: %d\n", get_right_sensor_value());
    printf("left sensor: %d\n",get_left_sensor_value());
    printf("front sensor: %d\n", get_front_sensor_value());
    printf("can move %d\n", can_move());
    //my_mouse->solve_maze();


    mouse_x = 5;
    mouse_y = 0;
    direction = WEST;
    print_maze();
    printf("right sensor: %d\n", get_right_sensor_value());
    printf("left sensor: %d\n",get_left_sensor_value());
    printf("front sensor: %d\n", get_front_sensor_value());
    printf("can move %d\n", can_move());
}


// the front sensor is 0, then the mouse can move in this direction
bool Mouse:: can_move(){
    //in the real world, instead of using 0, we need to set some constant
    //as a threshold for the sensor value; 
    return (get_front_sensor_value()==0);
}

void Mouse:: adjust_direction(){


}


//Assumption: the maze[0][y] and maze[x][0] has left wall and bottom wall
void Mouse:: check_wall(){

    if(direction == NORTH){
        detected_maze[mouse_x][mouse_y]->right_wall = get_right_sensor_value();
        detected_maze[mouse_x][mouse_y]->top_wall = get_front_sensor_value();

    } else if(direction == SOUTH){
        detected_maze[mouse_x][mouse_y]->right_wall = get_left_sensor_value();
    } else if(direction == EAST){
        detected_maze[mouse_x][mouse_y]->right_wall = get_front_sensor_value();
        detected_maze[mouse_x][mouse_y]->top_wall = get_left_sensor_value();

    } else{ //WEST
        detected_maze[mouse_x][mouse_y]->top_wall = get_right_sensor_value();

    }
}

void Mouse:: check_neighbor(){
    Cell * curr;
    vector<Cell*> neighbor;
    int min_dist;

    vc.push_back(detected_maze[mouse_x][mouse_y]);

    while(!vc.empty()){

        curr = stk.back();
        stk.pop_back();

        min_dist = MAX;

        if(mouse_x < MAZE_SIZE-1){ //top cell
            if(detected_maze[mouse_x + 1][mouse_y]->dist != 0)
                neighbor.push_back(detected_maze[mouse_x + 1][mouse_y]);
        }

        if(mouse_y < MAZE_SIZE -1){ //right_cell
            if(detected_maze[mouse_x][mouse_y+1]->dist!= 0)
                neighbor.push_back(detected_maze[mouse_x][mouse_y+1]);
        }

        if(mouse_x > 0){ //left cell
            if(detected_maze[mouse_x-1][mouse_y]->dist != 0)
                neighbor.push_back(detected_maze[mouse_x-1][mouse_y]);
        }

        if(mouse_y > 0){ //bottom cell
            if (detected_maze[mouse_x][y-1]->dist != 0)
                neighbor.push_back(detected_maze[mouse_x][mouse_y-1]);
                
        }

        for (vector<Cell *>::iterator it = neighbor.begin(); it != neighbor.end(); it++) {
            if ((*it)->dist < min) {
                min = (*it)->dist;
            }
        }

        if(curr-dist){

        }
    }

}

void Mouse:: move_one_cell(){
	//Check and Add Wall
    check_wall();

    //Check_neighbor
    check_neighbor();

    //Adjust_direction

    //Move

}

void Mouse:: solve_maze(){
	
	//while the mouse has not find the center of the Maze
	while(!detected_maze->is_center(mouse_x, mouse_y)){
		move_one_cell();
	}
	

}

Mouse:: Mouse(){
    direction = NORTH;
    prev_dir = -1;

    mouse_x = 0;
    mouse_y = 0; 
    reference_maze = new Maze();  //we should not modify any thing inside reference_maze
    detected_maze = new Maze();

}
//==============================================================



int main(){

	Mouse * my_mouse = new Mouse();

    printf("Maze Format: [Row, Col]. Size %d by %d\n", MAZE_SIZE, MAZE_SIZE);
    
    cout << "Start at the bottom leftmost corner [0,0]." << endl;

    // while(1){
    //     cout << "Select the Maze that you wish to solve" << endl;
    //     cout << "Type in [test1] or [test2] or [size6]" << endl;
    //     char tmp[101];
    //     scanf("%100s", tmp);
    //     string file_name = tmp;

    //     if(file_name.compare("test1") == 0){
    //         my_mouse->load_maze("test1.txt");
    //         break;
    //     }
    //     if(file_name.compare("test2") == 0){
    //         my_mouse->load_maze("test2.txt");
    //         break;
    //     }
    //     if(file_name.compare("size6") == 0){
    //         my_mouse->load_maze("size6.txt");
    //         break;
    //     }
    // }
    my_mouse->load_maze("size6.txt");

	printf("Here is the inital Maze:\n"); 
    my_mouse->print_reference_maze();
    
    printf("Let's see how the Mouse is going to solve it:\n");
    my_mouse->print_maze();

    //my_mouse->test_sensor();
    

}