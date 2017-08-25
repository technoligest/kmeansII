
#include <iostream>
#include <fstream>
#include <random>
#include "experiments/experiments.h"
#include "handlers/data_reader.h"
#include "experiments/experiment_analyzer2.h"
#include "experiments/convex_hull.h"

using namespace std;

int main(int argc, char **argv) {
  ifstream inputFile;
  inputFile.open("../inputFiles/DimRedFullDataComplete.txt");
  kmeans::Dataset dataset = kmeans::readDataset(inputFile);
  inputFile.close();
  using kmeans::operator<<;
  for(int l =0; l <10; ++l) {
    kmeans::experiments::ExperimentRunner e(dataset, );
    e.runExperiments(100);
    auto i = e.getExperiments();
    kmeans::experiments::reader::printExperiments("DimRedFullData.txt", i,
                                                  "/Users/yaseralkayale/Documents/classes/kmeansII/lib/experiments/Experiment Results");
  }
  std::cout << "Done" << std::endl;
  return 0;
}
