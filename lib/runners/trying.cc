/*
 * Class is for trying out difference things before adding them for
 * full productions.
 *
 */
#include <iostream>
#include <fstream>
#include <random>
#include "../experiments/experiments.h"
#include "../experiments/experiment_analyzer2.h"
#include "../experiments/convex_hull.h"
#include "../home.h"
#include "../algorithm/seed_pickers.h"
#include "../algorithm/lloyd_iteration_runner.h"

using namespace std;

int main(int argc, char **argv) {
  //input data
  ifstream inputFile;
  inputFile.open(home + "/inputFiles/DimRed10000.txt");
  if(!inputFile.good()){
    std::cout<< home << "/inputFiles/DimRed10000" << std::endl;
  }
  kmeans::Dataset dataset = kmeans::readDataset(inputFile);
  inputFile.close();

  using kmeans::operator<<;
  kmeans::NewSeedPicker sp(5,5);
  kmeans::LloydIterationRunner ir;

  kmeans::KmeansInstance <kmeans::NewSeedPicker, kmeans::LloydIterationRunner>inst(&ir,&sp);
  kmeans::Dataset centres;
  inst.cluster(dataset,10,centres);
  inst.print(std::cout);


  //
  ////kmeans::KmeansBase *kmeans = new kmeans::KmeansInstance<kmeans::NewSeedPicker, kmeans::LloydIterationRunner>(&ir,&sp);
  ////kmeans->cluster(dataset,10,)
  //
  //
  //
  //for(int l =0; l <10; ++l) {
  //
  //
  //  kmeans::experiments::ExperimentRunner e(dataset,);
  //  e.runExperiments(100);
  //  auto i = e.getExperiments();
  //  kmeans::experiments::reader::printExperiments("DimRedFullData.txt", i,
  //                                                "/Users/yaseralkayale/Documents/classes/kmeansII/lib/experiments/Experiment Results");
  //}
  //std::cout << "Done" << std::endl;
  return 0;
}
