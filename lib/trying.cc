
#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
#include <cxxabi.h>
#include "pkgs/dlib/optimization/max_cost_assignment.h"
#include "Experiments/experiments.hh"
#include "handlers/dataReader.hh"

using namespace std;
using namespace dlib;


//void insertMins(vector<double> &mins, double ran){
//  if(mins.empty()){
//    mins.push_back(ran);
//    return;
//  }
//  for(int i=0;i<mins.size();++i){
//    if(mins[i]<ran){
//      mins.insert(mins.begin()+i,ran);
//      break;
//    }
//  }
//}
//
//void print_vec(const std::vector<double>& vec)
//{
//  for (auto x: vec) {
//    std::cout << ' ' << x;
//  }
//  std::cout << '\n';
//}

int main(int argc, char **argv) {

  // Let's imagine you need to assign N people to N jobs.  Additionally, each person will make
  // your company a certain amount of money at each job, but each person has different skills
  // so they are better at some jobs and worse at others.  You would like to find the best way
  // to assign people to these jobs.  In particular, you would like to maximize the amount of
  // money the group makes as a whole.  This is an example of an assignment problem and is
  // what is solved by the max_cost_assignment() routine.
  //
  // So in this example, let's imagine we have 3 people and 3 jobs.  We represent the amount of
  // money each person will produce at each job with a cost matrix.  Each row corresponds to a
  // person and each column corresponds to a job.  So for example, below we are saying that
  // person 0 will make $1 at job 0, $2 at job 1, and $6 at job 2.


  //matrix<int> cost(3, 3);
  //cost = -2, -1, -6,
  //        -3, -5, -6,
  //        -4, -5, -0;
  //// To find out the best assignment of people to jobs we just need to call this function.
  //std::vector<long> assignment = max_cost_assignment(cost);
  //
  //// This prints optimal assignments:  [2, 0, 1] which indicates that we should assign
  //// the person from the first row of the cost matrix to job 2, the middle row person to
  //// job 0, and the bottom row person to job 1.
  //for (unsigned int i = 0; i < assignment.size(); i++)
  //  cout << assignment[i] << std::endl;
  //
  //// This prints optimal cost:  16.0
  //// which is correct since our optimal assignment is 6+5+5.
  //cout << "optimal cost: " << assignment_cost(cost, assignment) << endl;
  //matrix<int> costt(1, 1);
  //costt(0,0) = 50;
  //cout << costt << endl;

  ifstream inputFile;
  inputFile.open("/Users/Technoligest/Documents/Classes/Current/Norbert + Vlado/kmeansII/inputFiles/DimRedFullData.txt");
  Dataset d = readDataset(inputFile);
  ExperimentRunner e(d,50);
  e.RunExperiments(1);
  e.printResult("DimRedFullData");

  //inputFile.open("/Users/Technoligest/Documents/Classes/Current/Norbert + Vlado/kmeansII/cmake-build-debug/test1-fullData.txt");
  //std::vector<ExperimentResult> exp = readExperiments(inputFile);
  //ExperimentRunner ex(exp);
  //ex.printResult("FullData");

  return 0;
}
