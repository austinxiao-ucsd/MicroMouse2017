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
 //   int s = 0;

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

	if(mouse_x < 0 || mouse_y < 0){
		printf("Mouse_x and Mouse_y cannot be less than 0\n");
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

                if(y == mouse_x && j == mouse_y){
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


    bool has_wall;

	if(direction == NORTH){
		if(mouse_x == MAZE_SIZE-1){ //if the mouse is at the topest row;
			return 1;
		}

		has_wall = reference_maze->maze[mouse_x][mouse_y]->top_wall;
        detected_maze->maze[mouse_x][mouse_y]->top_wall = has_wall;

	}
	else if(direction == SOUTH){
		if(mouse_x == 0){
			return 1;
		}
		has_wall = reference_maze->maze[mouse_x-1][mouse_y]->top_wall; //its bottom cell's upper wall
        detected_maze->maze[mouse_x-1][mouse_y]->top_wall = has_wall;
	}
	else if(direction == EAST){
		if(mouse_y == MAZE_SIZE-1)
			return 1;
		
        has_wall = reference_maze->maze[mouse_x][mouse_y]->right_wall;
        detected_maze->maze[mouse_x][mouse_y]->right_wall = has_wall;
	}		
	else{ //WEST
		if(mouse_y == 0)
	 		return 1;
		has_wall = reference_maze->maze[mouse_x][mouse_y-1]->right_wall;
        detected_maze->maze[mouse_x][mouse_y-1]->right_wall = has_wall;

	}

    return has_wall;
}

bool Mouse:: get_left_sensor_value(){
    bool has_wall;

	if(direction == NORTH){
		if(mouse_y == 0) //if the mouse is at the left_most column
			return 1;
        
        has_wall = reference_maze->maze[mouse_x][mouse_y-1]->right_wall;
        detected_maze->maze[mouse_x][mouse_y-1]->right_wall = has_wall;

	}
	else if(direction == SOUTH){
		if(mouse_y == MAZE_SIZE-1)
			return 1;

        has_wall = reference_maze->maze[mouse_x][mouse_y]->right_wall;
        detected_maze->maze[mouse_x][mouse_y]->right_wall = has_wall;

	}
	else if(direction == EAST){
		if(mouse_x == MAZE_SIZE-1)
			return 1;

        has_wall = reference_maze->maze[mouse_x][mouse_y]->top_wall;
        detected_maze->maze[mouse_x][mouse_y]->top_wall = has_wall;

	}
	else{
		if(mouse_x == 0)
			return 1;
		has_wall = reference_maze->maze[mouse_x-1][mouse_y]->top_wall;
        detected_maze->maze[mouse_x-1][mouse_y]->top_wall = has_wall;
	}

    return has_wall;
}




bool Mouse:: get_right_sensor_value(){

    bool has_wall;

	if(direction == NORTH){
		if(mouse_y == MAZE_SIZE-1) //if the mouse is at the right_most column
			return 1;

		has_wall = reference_maze->maze[mouse_x][mouse_y]->right_wall;
        detected_maze->maze[mouse_x][mouse_y]->right_wall = has_wall;

	}
	else if(direction == SOUTH){
		if(mouse_y == 0)
			return 1;

		has_wall = reference_maze->maze[mouse_x][mouse_y-1]->right_wall;
        detected_maze->maze[mouse_x][mouse_y-1]->right_wall = has_wall;

	}
	else if(direction == EAST){
		if(mouse_x == 0)
			return 1;

		has_wall = reference_maze->maze[mouse_x-1][mouse_y]->top_wall;
        detected_maze->maze[mouse_x-1][mouse_y]->top_wall = has_wall;
	}
	else{
		if(mouse_x == MAZE_SIZE-1)
			return 1;

		has_wall = reference_maze->maze[mouse_x][mouse_y]->top_wall;
        detected_maze->maze[mouse_x][mouse_y]->top_wall = has_wall;

	}

    return has_wall;

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


//Assumption: the maze[0][y] and maze[x][0] has left wall and bottom wall
void Mouse:: check_open_neighbor(){

    right_sensor = get_right_sensor_value();
    front_sensor = get_front_sensor_value();
    left_sensor = get_left_sensor_value();
    print_sensor_reading();


    if(direction == NORTH){

        if(prev == SOUTH){
            south_open = 1;
        }

        north_open = !front_sensor;
        east_open = !right_sensor;
        west_open = !left_sensor;


    } else if(direction == SOUTH){

        if(prev == NORTH){
            north_open = 1;
        }

        south_open = !front_sensor;
        east_open = !left_sensor;
        west_open = !right_sensor;

    } else if(direction == EAST){

        if(prev == WEST){
            west_open = 1;
        }

        south_open = !right_sensor;
        east_open = !front_sensor;
        north_open = !left_sensor;
       

    } else{ //WEST

        if(prev == EAST){
            east_open = 1;
        }

        south_open = !left_sensor;
        west_open = !front_sensor;
        north_open = !right_sensor;
    }

    printf("finish checking neighbor and adding walls\n");
}


/* Check the minimum from a set of neighboring cells */
int Mouse:: min_open_neighbor(vector<Cell*> cells) {
    int min = MAX;
    for (vector<Cell *>::iterator it = cells.begin(); it != cells.end(); it++) {
        if ((*it)->dist < min) {
            min = (*it)->dist;
        }
    }
    // printf("min %d\n", min);
    return min;
}


void Mouse:: update_distance(){
    Cell * curr;
    vector<Cell*> neighbor;
    vector<Cell*> open_neighbor;
    int min_dist;
    int x, y;
    int count = 0;


    stk.push_back(detected_maze->maze[mouse_x][mouse_y]);

    //printf("curr dist: %d\n", curr->dist);
    // while(!stk.empty()){
    while(!stk.empty()){
       

        curr = stk.back();
        stk.pop_back();
        
        x = curr->x;
        y = curr->y;

        if(x < MAZE_SIZE-1){ //top cell
            neighbor.push_back(detected_maze->maze[x+1][y]);
            // if(north_open)
            //     open_neighbor.push_back(detected_maze->maze[mouse_x + 1][mouse_y]);
            if(!curr->top_wall){
                open_neighbor.push_back(detected_maze->maze[x + 1][y]);
            }
          
        }


        if(y > 0){ //left cell
            neighbor.push_back(detected_maze->maze[x][y-1]);
            
            if (!(detected_maze->maze[x][y - 1]->right_wall)) {
                open_neighbor.push_back(detected_maze->maze[x][y - 1]);
            }
            // if(west_open)
            //     open_neighbor.push_back(detected_maze->maze[mouse_x][mouse_y-1]);

        }

        if(x > 0){ //bottom cell
            neighbor.push_back(detected_maze->maze[x-1][y]);
            if (!(detected_maze->maze[x-1][y]->top_wall)) {
                open_neighbor.push_back(detected_maze->maze[x-1][y]);
            }
            // if(south_open)
            //     open_neighbor.push_back(detected_maze->maze[mouse_x-1][mouse_y]);
        }

        if(y < MAZE_SIZE -1){ //right_cell
            neighbor.push_back(detected_maze->maze[x][y+1]);
            // if(east_open)
                // open_neighbor.push_back(detected_maze->maze[mouse_x][mouse_y+1]);
            if(!curr->right_wall){
                open_neighbor.push_back(detected_maze->maze[x][y+1]);
            }
        }


  

      

     

        if (open_neighbor.empty()) {
            printf("This should never happen, error\n");
            neighbor.clear();
            continue;
        }

    

        min_dist = min_open_neighbor(open_neighbor);
  
        open_neighbor.clear();

        //printf("count %d with current cell <%d, %d>, dist: %d\n", count, curr->x, curr->y, curr->dist);

        if (curr->dist - 1 != min_dist) {
            curr->dist = min_dist + 1;
            for (vector<Cell *>::iterator it = neighbor.begin(); it != neighbor.end(); it++) {
                if (!detected_maze->is_center(*it)) {
                    stk.push_back(*it);
                }
            }
            neighbor.clear();
        }

        
        // if(count < 10 ){
        //     detected_maze->print_maze();
        //     if(!stk.empty()){
        //         printf("Elements in the stack\n");
        //         for (vector<Cell *>::iterator it = stk.begin(); it != stk.end(); it++) {
        //             printf("<%d,%d>, %d\n", (*it)->x, (*it)->y, (*it)->dist);
        //         }
        //         printf("\n");
        //     }
        // }

        count++;
    }
    printf("Finishing updating the distance\n");

}



void Mouse:: print_open_direction(){

    printf("north open: %d ", north_open);
    printf("south open: %d ", south_open);
    printf("east open: %d ", east_open);
    printf("west open: %d\n", west_open);
}

void Mouse:: print_sensor_reading(){
    printf("current direction: %d\n", direction);
    printf("right sensor: %d ", get_right_sensor_value());
    printf("left sensor: %d ",get_left_sensor_value());
    printf("front sensor: %d\n", get_front_sensor_value());
}

void Mouse:: move_one_cell(){
	//check the open neighbor and update the wall at the same time
    printf("CURRENT MOUSE POSITION <%d, %d>\n", mouse_x, mouse_y);
    printf("prev direction is %d\n", prev);
    printf("current direction is %d\n", direction);

    check_open_neighbor();

    // printf("finish checking open neighbor\n");
    //update the distance properly
    update_distance();

    // printf("update_distance\n");

    //pick the next cell and adjust_direction

    print_sensor_reading();
    print_open_direction();
    
    int min_dist = MAX;
    int temp;
    if(north_open){
        temp = detected_maze->maze[mouse_x+1][mouse_y]->dist;
        if (temp < min_dist) {
            min_dist = temp;
            direction = NORTH;
            prev = SOUTH;
        }
       
    }
    
    // printf("after checking north\n");
    if(south_open){
        temp = detected_maze->maze[mouse_x-1][mouse_y]->dist;
        if (temp < min_dist){
            min_dist = temp;
            direction = SOUTH;
            prev = NORTH;

        }
    }
    // printf("after checking south\n");
    
    if(east_open){
        temp = detected_maze->maze[mouse_x][mouse_y+1]->dist;
        if (temp < min_dist){
            min_dist = temp;
            direction = EAST;
            prev = WEST;

        }
    }
    // printf("after checking east\n");
     
    if(west_open){
        temp = detected_maze->maze[mouse_x][mouse_y-1]->dist;
        if (temp < min_dist) {
            min_dist = temp;
            direction = WEST;
            prev = EAST;
        }
      
    }

    printf("Current direction with dist %d %d\n", direction, detected_maze->maze[mouse_x][mouse_y]->dist);
   
    // printf("Finishing pick the next cell\n");


    //Move
    if(direction == NORTH){
        mouse_x += 1;
    }
    else if(direction == SOUTH){
        mouse_x -= 1;
    }
    else if (direction == EAST){
        mouse_y += 1;
    }
    else{ //WEST
        mouse_y -= 1;
    }

    north_open = 0;
    south_open = 0;
    east_open = 0;
    west_open = 0;

    printf("Finishing Reset, METHOD ENDS\n");

}

void Mouse:: solve_maze(){
	
	//while the mouse has not find the center of the Maze
	while(!detected_maze->is_center(mouse_x, mouse_y)){
		move_one_cell();
        print_maze();
	}
	

}

Mouse:: Mouse(){
    direction = NORTH;
    prev = -1;

    north_open = 0;
    south_open = 0;
    east_open = 0;
    west_open = 0;

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
    my_mouse->load_maze("apec2016.txt");

	printf("Here is the inital Maze:\n"); 
    my_mouse->print_reference_maze();
    
    printf("Let's see how the Mouse is going to solve it:\n");

    for (int i = 0; i < MAZE_SIZE; i++){
        for (int j = 0; j < MAZE_SIZE; j++){
            if(my_mouse->reference_maze->maze[i][j]->x != i || my_mouse->reference_maze->maze[i][j]->y != j){
                printf("Supposed to be <%d,%d> but is <%d,%d>\n", i, j, my_mouse->reference_maze->maze[i][j]->x, my_mouse->reference_maze->maze[i][j]->y);
            } 
        
        }
    }   

    my_mouse->solve_maze();
    
    // my_mouse->print_maze();     //<position <0,0>
    // my_mouse->move_one_cell();

    // my_mouse->print_maze();     //<position <1,0>
    // my_mouse->move_one_cell();

    // my_mouse->print_maze();     //<position <1,1>
    // my_mouse->move_one_cell();

    // my_mouse->print_maze();     //<position <2,1>
    // my_mouse->move_one_cell();

    // // // //after moving:
    // // my_mouse->print_maze();     //position <2,0>

    // my_mouse->print_maze();     //position <2,0>
    // my_mouse->move_one_cell();

    // my_mouse->print_maze();     //position <3,0>
    // my_mouse->move_one_cell();


    //my_mouse->test_sensor();
    

}