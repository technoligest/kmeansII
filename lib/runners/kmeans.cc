//
// Created by Yaser Alkayale on 2017-08-28.
//

/*
 * Run a single kmeans instance with any given commandLine args. To know the args needed,
 * just run the program without any args.
 */
#include <iostream>
#include <cassert>
#include "../algorithm/kmeans.h"

using std::endl;
using std::cout;

int main(int argc, char **argv) {
  //std::cout << "Algorithm: " << args.algorithm << " l:" << args.l << " r: " << args.r << " dataset is: "
  //          << dataset.size() << "X" << dataset[0].size() << std::endl;
  kmeans::KmeansArgs args;
  if(!args.parse_args(argc, argv)) {
    std::cout << "Usage: ./kmeans -i <inputFile> -a <algorithm name> -k <k value>" << std::endl;
    return 1;
  }
  kmeans::NewSeedPicker newSeedPicker(args.l, args.r);
  kmeans::LloydIterationRunner lloydIterationRunner(200);
  kmeans::KmeansBase *algo;
  if(args.algorithm == "kmeans") {
    algo = new kmeans::Kmeans<>();
  } else if(args.algorithm == "kmeans++") {
    algo = new kmeans::Kmeanspp<>();
  } else if(args.algorithm == "kmeansNew") {
    assert(args.l != -1 && args.r != -1);
    algo = new kmeans::KmeansConsensus<>(&lloydIterationRunner, &newSeedPicker);
  } else if(args.algorithm == "kmeansII") {
    assert(args.l != -1 && args.r != -1);
    algo = new kmeans::KmeansII<kmeans::LloydIterationRunner, kmeans::LloydIterationRunner>(args.l, args.r);
  } else {
    std::cout << "Inputted algorithm [" << args.algorithm
              << "] is not found. Please enter one of (kmeans, kmeans++ or kmeansII).";
    exit(1);
  }

  std::ifstream inputFile;
  inputFile.open(args.inputFileName);
  assert(inputFile.good());
  kmeans::Dataset dataset = kmeans::readCSVDataset(inputFile);



  std::vector<kmeans::Instance> centres;

  algo->cluster(dataset, args.k, centres);

  using kmeans::operator<<;

  std::ofstream realOutFile;
  std::ofstream optionsOutFile;
  if(args.outputFileName != "none") {
    realOutFile.open(args.outputFileName, std::ios::out);
    optionsOutFile.open(args.outputFileName + ".extra", std::ios::out);
  }
  std::ostream &o = (args.outputFileName != "none") ? realOutFile : std::cout;
  std::ostream &o2 = (args.outputFileName != "none") ? optionsOutFile : std::cout;
  for(auto centre:centres) {
    o << centre << std::endl;
  }
  o2 << "Input:" << args.inputFileName << std::endl;
  o2 << "Iterations time:" << algo->iterationRunnerTime() << std::endl;
  o2 << "Seeding tim:" << algo->seedPickerTime() << std::endl;
  o2 << "Distance squared:" << algo->distanceSquared() << endl;
  realOutFile.flush();
  realOutFile.close();
  optionsOutFile.flush();
  optionsOutFile.close();

  delete algo;
  return 0;
}

//l:5 r:5   k:50file: /Users/yaseralkayale/Documents/classes/current/honours/kmeansII/generatedFiles/datasets/dataset0.csv
//l:-1 r:-1 k:5file:  /Users/yaseralkayale/Documents/classes/current/honours/kmeansII/generatedFiles/datasets/dataset0.csv

