#include<iostream>
#include<fstream>
#include<list>

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
    list<SensorData> data;
    SensorData getnext();

  private:
    int iter;
};

Parser::Parser(void){
  iter = 0;
  string file_name = "data.txt";
  ifstream input_stream(file_name);
  if (!input_stream) cerr << "Can't open input file!";
  list<SensorData> sensor_data;
  string line;
  while (getline(input_stream, line)) {
    struct SensorData currentdata;
    currentdata.cell_x = line[0];
    currentdata.cell_y = line[1];
    currentdata.left = line[2];
    currentdata.right = line[3];
    data.push_back(currentdata);
  }
}

SensorData Parser::getnext(){
  struct SensorData toreturn;
  unsigned N = iter;
  if (data.size() > N){
    std::list<SensorData>::iterator it = data.begin();
    std::advance(it, N);
    toreturn = *it;
    iter += 1;
  }
  else{
    cout<<"End of List"<<endl;
  }
  return toreturn;
}

int main(){
}
