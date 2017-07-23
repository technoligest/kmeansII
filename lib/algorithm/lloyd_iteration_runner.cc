//
// Created by Yaser Alkayale on 2017-07-07.
//

#include <cmath>
#include <limits>
#include "lloyd_iteration_runner.h"

namespace kmeans{
/*
 * Returns the sum distance squared of each point to its cluster centre of the PREVIOUS iteration
 */
Distance LloydIterationRunner::runLloydIteration(const Dataset &dataset, const Weights &weights, Dataset &centres) {
  size_t n = dataset.size(); //number of points in the dataset
  ull k = centres.size();    //number of clusters

  Dataset newCentres = Dataset(k, Instance(centres[0].size(), 0));
  std::vector<size_t> newCentreSizes(k, 0);

  Distance totalDistance = 0;
  //adding each instance to where it belongs
  for(int instId = 0; instId < n; ++instId) {
    const Instance &inst = dataset[instId];
    auto minDistClusterId = helpers::findBelongingCentrePosition(inst, centres);
    newCentres[minDistClusterId] += inst;
    newCentreSizes[minDistClusterId] += 1;
    totalDistance += helpers::findDistanceSquared(inst, centres[minDistClusterId]);
  }
  for(size_t i = 0; i < newCentres.size(); ++i) {
    if(newCentreSizes[i] > 1) {
      for(auto &centreItem:newCentres[i]) {
        centreItem /= newCentreSizes[i];
      }
    }
  }
  centres = newCentres;
  ++num_iterations_;
  return totalDistance;
}

Distance LloydIterationRunner::runLloydIterations(const Dataset &dataset, const Weights &weights, Dataset &centres) {
  if(dataset.empty() || centres.empty() || dataset.size() < centres.size()) {
    return -1;
  }
  double currDistance = std::numeric_limits<double>::max();
  double bestDistance = std::numeric_limits<double>::max();
  for(ull i = 0; i < MAX_NUM_ITERATIONS; ++i) {
    double newDistance = runLloydIteration(dataset, weights, centres);
    if(newDistance < bestDistance) {
      bestDistance = newDistance;
    }
    if(newDistance > currDistance * LOCAL_ITERATION_BIAS) {
      std::cout << "Terminating because iteration has exceeded local bias." << std::endl;
      break;
    }
    if(fabs(newDistance - currDistance) < CONVERGENCE_THREASHOLD) {
      std::cout << "Terminating because iterations are stable." << std::endl;
      break;
    }
    currDistance = newDistance;
  }
  std::cout << "numIterations: " << num_iterations_ << std::endl;
  return bestDistance;
}

}//namespace kmeans