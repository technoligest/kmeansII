//
// Created by Yaser Alkayale on 2017-07-14.
//
#include <fstream>
#include "experiment_runner.h"

namespace kmeans{
namespace experiments{
bool ExperimentRunner::printResult(std::string dataSetName) {
  /*
   * Finding the next number to enter for the test
   * Taking the max of the 3 prefixes for each of the algorithms.
   */
  std::string dir = "/Users/Technoligest/Documents/Classes/Current/Norbert + Vlado/kmeansII/lib/experiments/Experiment Results";
  ull num = std::max(helpers::lastNumberedFile(
      dir, "kmeans-" + dataSetName + "-test"), std::max(helpers::lastNumberedFile(dir,
                                                                                  "kmeans++-" +
                                                                                  dataSetName +
                                                                                  "-test"),
                                                        helpers::lastNumberedFile(dir,
                                                                                  "kmeans||-" +
                                                                                  dataSetName +
                                                                                  "-test")));


  std::string postFix = "-" + dataSetName + "-test" + std::to_string(num) + ".txt";
  std::ofstream kOutputFile(dir + "/kmeans" + postFix);
  std::ofstream kppOutputFile(dir + "/kmeans++" + postFix);
  std::ofstream k2OutputFile(dir + "/kmeans||" + postFix);
  for(const auto &i: results) {
    if(i.algorithm == "Kmeans") {
      kOutputFile << i << std::endl;
    } else if(i.algorithm == "Kmeans++") {
      kppOutputFile << i << std::endl;
    } else if(i.algorithm == "Kmeans||") {
      k2OutputFile << i << std::endl;
    }
  }
  kOutputFile.flush();
  kOutputFile.close();
  kppOutputFile.flush();
  kppOutputFile.close();
  k2OutputFile.flush();
  k2OutputFile.close();
  return true;
}
void ExperimentRunner::runExperiments(ull numExperiments) {
  KmeansBase *kmeans;
  kmeans = new Kmeans<LloydIterationRunner>();
  for(ull i = 0; i < numExperiments; ++i) {
    runAlg(kmeans, "Kmeans");
  }
  delete kmeans;

  kmeans = new Kmeanspp<LloydIterationRunner>();
  for(ull i = 0; i < numExperiments; ++i) {
    runAlg(kmeans, "Kmeans++");
  }
  delete kmeans;

  kmeans = new KmeansII<LloydIterationRunner, LloydIterationRunner>(2 * k, 5);
  for(ull i = 0; i < numExperiments; ++i) {
    runAlg(kmeans, "Kmeans||");
  }
  delete kmeans;
}

} // namspace experiments
} // namespace kmeans
