
//#include "handlers/dataReader.h"
#include <iostream>
#include <fstream>
#include "algorithm/kmeans.h"
#include "experiments/experiments.h"
#include "handlers/data_reader.h"


#define NumIterations 100


using namespace std;


int main(int argc, char **argv) {
  ifstream inputFile;
  inputFile.open("../inputFiles/DimRedFullData.txt");
  kmeans::Dataset d = kmeans::readDataset(inputFile);
  using kmeans::operator<<;
  std::cout << d << std::endl;
  kmeans::experiments::ExperimentRunner e(d,50);
  e.runExperiments(1);
  auto result = e.getExperiments();
  kmeans::experiments::reader::printExperiments("DimRedFullData",result);
  return 0;
}

