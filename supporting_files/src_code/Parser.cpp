#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

struct SensorData{
  int cell_x;
  int cell_y;
  double left;
  double right;
};

class Parser{
  public:
    Parser();
    //list<SensorData> data;
    vector<SensorData> data;
    vector<double> errors;
    bool has_next();
    void next();
    double get_left();
    double get_right();
    void write();

  private:
    int iter;
    vector<string> split(const string &s, char delim);
};

Parser::Parser(void){
  iter = 0;
  string file_name = "input.dat";
  ifstream input_stream(file_name);
  if (!input_stream) cerr << "Can't open input file!";
  string line;
  while (getline(input_stream, line)) {
    cout << "Line" << line<<endl;
    struct SensorData current_data;

    string buf;
    stringstream ss(line);
    vector<string> splitted;
    while (ss >> buf){
      splitted.push_back(buf);
    }

    current_data.cell_x = stod(splitted[0]);
    current_data.cell_y = stod(splitted[1]);
    current_data.left = stod(splitted[2]);
    current_data.right = stod(splitted[3]);
    cout<< current_data.cell_x<<" "<<current_data.cell_y<<" "<<current_data.left << " " << current_data.left<<endl;
    data.push_back(current_data);
  }

  cout << "Parser: constructor" << endl;

  for (int i = 0; i < data.size(); i++) {
    //unsigned N = iter;
    //list<SensorData>::iterator it = data.begin();
    //advance(it, N);
    
    //cout<< it->left<<" " << it->right<<endl;
    cout<<data[iter].left<<" "<<data[iter].right<<endl;
    iter += 1;
  }
}

bool Parser::has_next(){
  return (iter<data.size());
}

void Parser::next(){
  struct SensorData to_return;
  //unsigned N = iter;
  if (data.size() > iter){
    //list<SensorData>::iterator it = data.begin();
    //advance(it, N);
    //toreturn = *it;
    to_return = data[iter];
    iter += 1;
  }
  else{
    cout<<"End of List"<<endl;
  }
}

double Parser::get_left(){
  //list<SensorData>::iterator it = data.begin();
  //advance(it, iter);
  //return it->left;
  return data[iter].left;
}

double Parser::get_right(){
  //list<SensorData>::iterator it = data.begin();
  //advance(it, iter);
  //return it->right;
  return data[iter].right;
}

void Parser::write(double error_to_write){
  errors.push_back(error_to_write);
}


