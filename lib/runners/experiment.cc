//
// Created by Yaser Alkayale on 2017-08-31.
//
/*
 * Run an experiment with the commandLine. All values are provided using commandLine args
 * For help to use it just run the program without any args.
 */

#include "../experiments/experiments_input_arguments.h"
#include "../experiments/experiments.h"

int main(int argc, char **argv) {
  kmeans::experiments::KmeansExperimentsArgs args;
  if(!args.parse_args(argc, argv))
    return 1;
  std::ifstream inputFile(args.inputFileName);
  kmeans::Dataset dataset = kmeans::readDataset(inputFile);
  kmeans::experiments::ExperimentRunner runner(dataset, args.k, args.l, args.r);
  runner.runExperiments(args.numExperiments);

  if(args.outputFileName != "none") {
    std::ofstream realOutFile;
    realOutFile.open(args.outputFileName, std::ios::out);
    for(auto experiment:runner.getExperiments()) {
      realOutFile << experiment << std::endl;
    }
    realOutFile.flush();
    realOutFile.close();
  }
  else{
    for(auto experiment:runner.getExperiments()) {
      std::cout << experiment << std::endl;
    }
  }
  return 0;
}