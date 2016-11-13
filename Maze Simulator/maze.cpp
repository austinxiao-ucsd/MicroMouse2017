/*
 * Hongda Xiao - UC San Diego
 * hoxiao@ucsd.edu
 * 
 * This class implements the Flood-fill algorithm,
 * constructs and prints the maze structure.
 */
#include "maze.h"
#include "math.h"

// maze predefined size is 16
Cell *maze[MAZE_SIZE][MAZE_SIZE];
// resulting path
vector<Cell*> res;


/*
* Calculates the total number of cells needed to get from a point (x1, y1)
* to a point (x2, y2).
*/
int manhattan_dist(int x1, int x2, int y1, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

/*
* Function that takes the minimum of the four given distances
*/
int min4(int a, int b, int c, int d) {
    int min;
    (a < b) ? min = a : min = b;
    if (c < min) min = c;
    if (d < min) min = d;
    return min;
}

/*
* Initializes the maze using the manhattan distances as the starting distances.
*/
void init_maze() {
    int goal1 = MAZE_SIZE / 2;
    int goal2 = (MAZE_SIZE - 1) / 2;
    for (int i = 0; i < MAZE_SIZE; i++) {
        for (int j = 0; j < MAZE_SIZE; j++) {
            // Distance of the cell will be the minimum distance to the closest
            // one out of four middle destination cells.
            maze[i][j] = new Cell(i, j, min4(manhattan_dist(i, goal1, j, goal1),
                                             manhattan_dist(i, goal1, j, goal2),
                                             manhattan_dist(i, goal2, j, goal1),
                                             manhattan_dist(i, goal2, j, goal2)));
            if (i == MAZE_SIZE - 1) {
                maze[i][j]->top_wall = true;
            }
            if (j == MAZE_SIZE - 1) {
                maze[i][j]->right_wall = true;
            }
        }
    }
}

/* Check the minimum from a set of neighboring cells */
int min_open_neighbor(vector<Cell*> cells) {
    int min = UCHAR_MAX;
    for (vector<Cell *>::iterator it = cells.begin(); it != cells.end(); it++) {
        if ((*it)->dist < min) {
            min = (*it)->dist;
        }
    }
    return min;
}

/* Determine if the maze center is found. */
bool is_center(Cell *cell) {
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

/*
* Implementation of the flood-fill algorithm
*/
void update_distances(vector <Cell*> &stack) {
    Cell *current;
    vector<Cell*> open_neighbors;
    vector<Cell*> neighbors;

    int x, y;
    int min;
    while (!stack.empty()) {
        current = stack.back();
        stack.pop_back();
        x = current->x;
        y = current->y;
        if (is_center(current)) {
            continue;
        }
        // check top neighbor
        if (y < MAZE_SIZE - 1) {
            neighbors.push_back(maze[y + 1][x]);
            if (!current->top_wall) {
                open_neighbors.push_back(maze[y + 1][x]);
            }
        }
        // check right neighbor
        if (x < MAZE_SIZE - 1) {
            neighbors.push_back(maze[y][x + 1]);
            if (!current->right_wall) {
                open_neighbors.push_back(maze[y][x + 1]);
            }
        }
        // check bottom neighbor
        if (y > 0) {
            neighbors.push_back(maze[y - 1][x]);
            if (!maze[y - 1][x]->top_wall) {
                open_neighbors.push_back(maze[y - 1][x]);
            }
        }
        // check left neighbor
        if (x > 0) {
            neighbors.push_back(maze[y][x - 1]);
            if (!maze[y][x - 1]->right_wall) {
                open_neighbors.push_back(maze[y][x - 1]);
            }
        }
        if (open_neighbors.empty()) {
            neighbors.clear();
            continue;
        }
        min = min_open_neighbor(open_neighbors);
        open_neighbors.clear();
        if (current->dist - 1 != min) {
            current->dist = min + 1;
            for (vector<Cell *>::iterator it = neighbors.begin(); it != neighbors.end(); it++) {
                if (!is_center(*it)) {
                    stack.push_back(*it);
                }
            }
            neighbors.clear();
        }
    }
}

/* Printing the maze */
void print_maze() {

    // print top wall
    for (int i = 0; i < MAZE_SIZE; i++) {
        cout << "+---";
    }
    cout << "+\n";

    int rows = MAZE_SIZE + (MAZE_SIZE - 1);
    int y;

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
                //      printf("   ");
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
        printf("\n");
    }
    for (int i = 0; i < MAZE_SIZE; i++) {
        printf("+---");
    }
    printf("+\n\n");
}

/* Traverse the maze and update the distances. */
void explore(vector<Cell*> &stack, int y, int x) {
    if (maze[y][x]->visited) {
        return;
    }
    else {
        maze[y][x]->visited = true;
    }
    if (maze[y][x]->top_wall || maze[y][x]->right_wall) {
        stack.push_back(maze[y][x]);
        update_distances(stack);
    }
    // if mouse is located bottom left of center then we want to prioritize exploring top/right
    if (y < MAZE_SIZE / 2 && x < MAZE_SIZE / 2) {
        // explore top
        if (y < MAZE_SIZE - 1) {
            explore(stack, y + 1, x);
        }
        // explore right
        if (x < MAZE_SIZE - 1) {
            explore(stack, y, x + 1);
        }
        // explore down
        if (y > 0) {
            explore(stack, y - 1, x);
        }
        // explore left
        if (x > 0) {
            explore(stack, y, x - 1);
        }
    }
    // if mouse is located top left of center then we want to prioritize exploring bottom/right
    else if (y > MAZE_SIZE / 2 && x < MAZE_SIZE / 2) {
        // explore right
        if (x < MAZE_SIZE - 1) {
            explore(stack, y, x + 1);
        }
        // explore down
        if (y > 0) {
            explore(stack, y - 1, x);
        }
        // explore top
        if (y < MAZE_SIZE - 1) {
            explore(stack, y + 1, x);
        }
        // explore left
        if (x > 0) {
            explore(stack, y, x - 1);
        }
    }
    // if mouse is located top right of center then we want to prioritize exploring bottom/left
    else if (y > MAZE_SIZE / 2 && x > MAZE_SIZE / 2) {
        // explore down
        if (y > 0) {
            explore(stack, y - 1, x);
        }
        // explore left
        if (x > 0) {
            explore(stack, y, x - 1);
        }
        // explore top
        if (y < MAZE_SIZE - 1) {
            explore(stack, y + 1, x);
        }
        // explore right
        if (x < MAZE_SIZE - 1) {
            explore(stack, y, x + 1);
        }
    }
    // if mouse is located bottom right of center then we want to prioritize exploring bottom/right
    else if (y < MAZE_SIZE / 2 && x > MAZE_SIZE / 2) {
        // explore left
        if (x > 0) {
            explore(stack, y, x - 1);
        }
        // explore top
        if (y < MAZE_SIZE - 1) {
            explore(stack, y + 1, x);
        }
        // explore down
        if (y > 0) {
            explore(stack, y - 1, x);
        }
        // explore right
        if (x < MAZE_SIZE - 1) {
            explore(stack, y, x + 1);
        }
    }
}

void load_maze(string file_name) {
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

/* Helper function for path printing. */
Cell* next_move(Cell *current){
    Cell * min_cell = current;
    int x = current->x, y = current->y;
    // check top
    if(x < MAZE_SIZE - 1){
        if(maze[y][x + 1]->dist < current->dist && maze[y][x]->right_wall == false){
            min_cell = maze[y][x + 1];
        }
    }
    if(y < MAZE_SIZE - 1){
        if(maze[y + 1][x]->dist < current->dist){
            min_cell = maze[y + 1][x];
        }
    }
    if(x > 0){
        if(maze[y][x - 1]->dist < current->dist){
            min_cell = maze[y][x - 1];
        }
    }
    if(y > 0){
        if(maze[y - 1][x]->dist < current->dist && maze[y - 1][x]->top_wall == false){
            min_cell = maze[y - 1][x];
        }
    }
    return min_cell;
}


/* Searching for the valid path */
void print_path(){
    Cell * curr = maze[0][0];
    while(!is_center(curr)){
        res.push_back(curr);
        curr = next_move(curr);
    }
    res.push_back(curr);
    cout << "Start -> ";
    for (vector<Cell *>::iterator it = res.begin(); it != res.end(); it++) {
        int x = (*it)->x;
        int y = (*it)->y;
        cout << "[ " << y  << " , " << x << " ] --> ";
    }
    cout << " End" << endl;
}



int main(){
    init_maze();
    cout << "Maze Format: [Row, Col]. Size: 10 by 10." << endl;
    cout << "Start at the bottom leftmost corner [0,0]." << endl;
    while(1){
        cout << "Type in [test1] or [test2]" << endl;
        char tmp[101];
        scanf("%100s", tmp);
        string file_name = tmp;

        if(file_name.compare("test1") == 0){
            load_maze("test1.txt");
            break;
        }
        if(file_name.compare("test2") == 0){
            load_maze("test2.txt");
            break;
        }
    }
    print_maze();

    while(1){
        cout << "Would you like to walk the maze now? Y/N" << endl;
        char ans[101];
        scanf("%100s", ans);
        string answer = ans;
        if(answer.compare("Y") == 0 || answer.compare("y") == 0){
            std::vector <Cell*> vc;
            vc.push_back(maze[0][0]);
            explore(vc, 0, 0);
            print_maze();
            break;
        }
        if(answer.compare("N") == 0 || answer.compare("n") == 0){
            break;
        }
    }

    while(1){
        cout << "Would you like to see the best path? Y/N" << endl;
        char ans[101];
        scanf("%100s", ans);
        string answer = ans;
        if(answer.compare("Y") == 0 || answer.compare("y") == 0){
            print_path();
            break;
        }
        if(answer.compare("N") == 0 || answer.compare("n") == 0){
            break;
        }
    }
}
