//
// Created by Yaser Alkayale on 2017-07-07.
//

#include <cmath>
#include "lloyd_iteration_runner.h"
#include "kmeans_helpers.h"

namespace kmeans{

Distance LloydIterationRunner::runLloydIteration() {
  if(dataset_.empty() || centres_.empty() || dataset_.size() < centres_.size()) {
    return -1;
  }

  Distance totalDistance = 0;
  std::vector<Instance> newCentres(centres_.size());
  std::vector<size_t> newCentreSizes(centres_.size());

  //resetting all the values
  std::fill(newCentreSizes.begin(), newCentreSizes.end(), 0);
  for(auto &centre:newCentres) {
    centre.resize(centres_[0].size());
    std::fill(centre.begin(), centre.end(), 0);
  }

  totalDistance = calculateBelongings(newCentreSizes,newCentres);
  recalculateCentres(newCentreSizes, newCentres);
  centres_ = newCentres;

  return totalDistance;
}

Distance LloydIterationRunner::runIterations() {
  if(dataset_.empty() || centres_.empty() || dataset_.size() < centres_.size()) {
    return -1;
  }

  std::vector<Instance> bestCentres;

  double currDistance = std::numeric_limits<double>::max();
  double bestDistance = std::numeric_limits<double>::max();
  int iteration;
  for(iteration = 0; iteration < MAX_NUM_ITERATIONS; ++iteration) {

    double newDistance = runLloydIteration();
    if(newDistance < bestDistance) {
      bestDistance = newDistance;
      bestCentres = centres_;
    }
    if(newDistance > currDistance * LOCAL_ITERATION_BIAS) {
      std::cout << "Terminating because iteration has exceeded local bias." << std::endl;
      break;
    }
    std::cout << "NewDist: " << newDistance << " CurrDist: " << currDistance << std::endl;
    if(fabs(newDistance - currDistance) < CONVERGENCE_THREASHOLD) {
      std::cout << "Terminating because iterations are stable." << std::endl;
      break;
    }
    currDistance = newDistance;
  }
  std::cout << "numIterations: " << iteration << std::endl;
  num_iterations_ = iteration;
  return bestDistance;
}


/*
 * Here we are given a vecotor of instances
 */
void LloydIterationRunner::recalculateCentres(const std::vector<size_t> newCentreSizes, std::vector<Instance> newCentres) {
  for(auto &centre: newCentres) {
    centre /= newCentreSizes;
  }
}


Distance LloydIterationRunner::calculateBelongings(std::vector<size_t> newCentreSizes, Dataset newCentres) {
  size_t m = centres_[0].size();
  Distance totalDistance = 0;

  //adding each instance to where it belongs
  for(int instId = 0; instId < dataset_.size(); ++instId) {
    const Instance &inst = dataset_[instId];
    auto minDistClusterId = helpers::findBelongingCentrePosition(inst, centres_);
    assert(newCentres[minDistClusterId].size() == m);
    newCentres[minDistClusterId] += inst;
    newCentreSizes[minDistClusterId] += weights_[instId];
    totalDistance += helpers::findDistanceSquared(inst, centres_[minDistClusterId]);
  }
  return totalDistance;
}

}//namespace kmeans