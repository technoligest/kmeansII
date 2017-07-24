//
// Created by Yaser Alkayale on 2017-07-14.
//
#include <fstream>
#include "experiment_runner.h"

namespace kmeans{
namespace experiments{

void ExperimentRunner::runAlg(KmeansBase *kmeans, const std::string& algName) {
  Dataset centres;
  ExperimentResult e;
  kmeans->cluster(d, k, centres);
  e.algorithm = algName;
  e.centres = centres;
  e.numIterations = kmeans->numIterations();
  e.distanceSquared = kmeans->distanceSquared();
  e.seedPickerTime = kmeans->seedPickerTime();
  e.iterationTime = kmeans->iterationRunnerTime();
  results.push_back(e);
}

void ExperimentRunner::runExperiments(ull numExperiments) {
  KmeansBase *kmeans;
  kmeans = new Kmeans<LloydIterationRunner>();
  for(ull i = 0; i < numExperiments; ++i) {
    runAlg(kmeans, "Kmeans");
  }
  //delete kmeans;

  kmeans = new Kmeanspp<LloydIterationRunner>();
  for(ull i = 0; i < numExperiments; ++i) {
    runAlg(kmeans, "Kmeans++");
  }
  //delete kmeans;

  kmeans = new KmeansII<LloydIterationRunner, LloydIterationRunner>(2 * k, 5);
  for(ull i = 0; i < numExperiments; ++i) {
    runAlg(kmeans, "Kmeans||");
  }
  //delete kmeans;
}

} // namspace experiments
} // namespace kmeans
