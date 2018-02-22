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
  using kmeans::operator<<;

  //input data
  std::string filename(HOME + "/generatedFiles/dataset4.csv");
  ifstream inputFile;
  inputFile.open(filename);
  if(!inputFile.good()) {
    std::cout << HOME << "/generatedFiles/dataset4.csv" << std::endl;
  }
  kmeans::Dataset dataset = kmeans::readCSVDataset(inputFile);
  inputFile.close();
  //std::cout << dataset << std::endl;
  //std::cout << dataset.size() << std::endl;
  //std::cout << dataset[0].size() << std::endl;


  kmeans::NewSeedPicker newSeedPicker(5, 5);
  kmeans::LloydIterationRunner lloydIterationRunner(175);
  kmeans::KmeansConsensus<> newAlgo(&lloydIterationRunner, &newSeedPicker);
  kmeans::Kmeanspp<> kmeanspp;
  kmeans::Kmeans<> kmeans;

  std::vector<double> newKmeansResult;
  std::vector<unsigned long long> kmeansppResults;
  std::vector<unsigned long long> kmeansResults;

  int max = 4;
  int k = 4;
  kmeans::Dataset centres;
  for(int i = 0; i < max; ++i) {
    newAlgo.cluster(dataset, k, centres);
    kmeans.cluster(dataset, k, centres);
    kmeanspp.cluster(dataset, k, centres);
    std::cout << newAlgo.distanceSquared() << std::endl<<std::endl;

    newKmeansResult.push_back(newAlgo.distanceSquared());
    kmeansResults.push_back(kmeans.distanceSquared());
    kmeansppResults.push_back(kmeanspp.distanceSquared());
  }
  for(auto i:newKmeansResult)
    std::cout<<i<<std::endl;
  std::cout << "kmeans: " << std::accumulate(kmeansResults.begin(), kmeansResults.end(), 0) << std::endl;
  std::cout << "kmeanspp: " << std::accumulate(kmeansppResults.begin(), kmeansppResults.end(), 0) << std::endl;
  std::cout << "kmeansnew: " << std::accumulate(newKmeansResult.begin(), newKmeansResult.end(), 0)  << std::endl;



  std::cout << "Done" << std::endl;
  std::cout<<std::numeric_limits<unsigned long long>::max();
  std::cout<<std::numeric_limits<unsigned long long>::min();
  return 0;
}
