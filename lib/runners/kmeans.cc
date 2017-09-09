//
// Created by Yaser Alkayale on 2017-08-28.
//
#include <iostream>
#include "../algorithm/kmeans.h"
#define DEBUG

int main(int argc, char **argv) {

  kmeans::KmeansArgs args;
  if(!args.parse_args(argc, argv))
    return 1;
  kmeans::KmeansBase *algo;
  if(args.algorithm == "kmeans") {
    algo = new kmeans::Kmeans<kmeans::LloydIterationRunner>();
  } else if(args.algorithm == "kmeans++") {
    algo = new kmeans::Kmeanspp<kmeans::LloydIterationRunner>();
  } else if(args.algorithm == "kmeans||") {
    algo = new kmeans::KmeansII<kmeans::LloydIterationRunner, kmeans::LloydIterationRunner>(2 * args.k, 5);
  } else {
    std::cout << "Inputted algorithm is not found. Please enter one of (kmeans, kmeans++ or kmeans||).";
    exit(1);
  }

  std::ifstream inputFile;
  inputFile.open(args.inputFileName);
  kmeans::Dataset dataset = kmeans::readDataset(inputFile);
  std::vector<kmeans::Instance> centres;
  algo->cluster(dataset, args.k, centres);

  using kmeans::operator<<;

  std::ofstream realOutFile;
  if(args.outputFileName != "none") {
    realOutFile.open(args.outputFileName, std::ios::out);
  }

  std::ostream &o = (args.outputFileName != "none") ? realOutFile : std::cout;
  for(auto centre:centres) {
    o << centre << std::endl;
  }

  return 0;
}