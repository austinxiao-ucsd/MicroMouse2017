#include "Maze.cpp"
#include "Mouse.h"

int main(){

	Maze * controller = new Maze();
	//controller->init_maze();

    controller->print_maze();

    cout << "Maze Format: [Row, Col]. Size: 10 by 10." << endl;
    cout << "Start at the bottom leftmost corner [0,0]." << endl;

    while(1){
        cout << "Type in [test1] or [test2] or [size6]" << endl;
        char tmp[101];
        scanf("%100s", tmp);
        string file_name = tmp;

        if(file_name.compare("test1") == 0){
            controller->load_maze("test1.txt");
            break;
        }
        if(file_name.compare("test2") == 0){
            controller->load_maze("test2.txt");
            break;
        }
        if(file_name.compare("size6") == 0){
            controller->load_maze("size6.txt");
            break;
        }
    }

    controller->print_maze();

    while(1){
        cout << "Would you like to walk the maze now? Y/N" << endl;
        char ans[101];
        scanf("%100s", ans);
        string answer = ans;
        if(answer.compare("Y") == 0 || answer.compare("y") == 0){
            std::vector <Cell*> vc;
            vc.push_back(maze[0][0]);
            controller->explore(vc, 0, 0);
            controller->print_maze();
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
            controller->print_path();
            break;
        }
        if(answer.compare("N") == 0 || answer.compare("n") == 0){
            break;
        }
    }
}