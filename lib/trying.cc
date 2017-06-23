
#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
#include <vector>
using namespace std;


void insertMins(vector<double> &mins, double ran){
  if(mins.empty()){
    mins.push_back(ran);
    return;
  }
  for(int i=0;i<mins.size();++i){
    if(mins[i]<ran){
      mins.insert(mins.begin()+i,ran);
      break;
    }
  }
}

void print_vec(const std::vector<double>& vec)
{
  for (auto x: vec) {
    std::cout << ' ' << x;
  }
  std::cout << '\n';
}

int main(int argc, char **argv) {
  //initializing random distribution
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(0, 1);
  double min = 1;
  vector<double> mins{0};
  for (int i = 0; i < 100000; ++i) {
    double ran = static_cast<double>(dis(gen));
    insertMins(mins,ran);
    if (ran < min) {
      min = ran;
    }
  }

  for(auto i:mins){
    cout<<i<<endl;
  }
  cout << "min: " << min << endl;
//  vector<double> d;
//  insertMins(d,4);
//  insertMins(d,4000);
//  insertMins(d,40);
//  print_vec(d);

  return 0;
}
