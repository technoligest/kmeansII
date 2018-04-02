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
using std::vector;

int main(int argc, char **argv) {
  kmeans::KmeansArgs args;
  if(!args.parse_args(argc, argv)) {
    std::cout << "Usage: ./kmeans -i <inputFile> -a <algorithm name> -k <k value>" << std::endl;
    return 1;
  }

  kmeans::NewSeedPicker newSeedPicker(args.l, args.r);
  kmeans::LloydIterationRunner lloydIterationRunner(200);
  kmeans::KmeansBase *algo;

  //Parsing the arguments and building the kmeans instance
  if(args.algorithm == "kmeans") {
    algo = new kmeans::Kmeans<>();
  } else if(args.algorithm == "kmeans++") {
    algo = new kmeans::Kmeanspp<>();
  } else if(args.algorithm == "kmeansNew") {
    if(args.l == -1 || args.r == -1) {
      cout << "kmeansNew requires you to input l and r values." << endl;
      exit(1);
    }
    algo = new kmeans::KmeansConsensus<>(&lloydIterationRunner, &newSeedPicker);
  } else if(args.algorithm == "kmeansII") {
    if(args.l == -1 || args.r == -1) {
      cout << "kmeansII requires you to input l and r values." << endl;
      exit(1);
    }
    algo = new kmeans::KmeansII<kmeans::LloydIterationRunner, kmeans::LloydIterationRunner>(args.l, args.r);
  } else {
    std::cout << "Inputted algorithm [" << args.algorithm
              << "] is not found. Please enter one of (kmeans, kmeans++ or kmeansII).";

  }

  std::ifstream inputFile;
  inputFile.open(args.inputFileName);
  if(inputFile.bad()) {
    cout << "Could not open the input file. Try again." << endl;
    exit(1);
  }


  //Running the algorithm on the given dataset and the given k
  kmeans::Dataset dataset = kmeans::readCSVDataset(inputFile);
  kmeans::Dataset centres;
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