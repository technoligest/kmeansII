//
// Created by Yaser Alkayale on 2017-07-12.
//


#include "kmeans_data.h"
#include <cassert>
#include <cmath>

namespace kmeans{
namespace utils{

/*
 * Confirm that all instances of the dataset have the same dimentianality.
 */
bool analyzeDataset(const Dataset &dataset) {
  auto baseSize = dataset[0].size();
  for(const Instance &i:dataset) {
    if(i.size() != baseSize) return false;
  }
  return true;
}

Distance distanceSquared(const Instance &instance1, const Instance &instance2) {
  if(instance1.size() != instance2.size())
    return -1;
  Distance result = 0;
  size_t size = instance1.size();
  for(int i = 0; i < size; ++i) {
    result += pow(instance1[i] - instance2[i], 2);
  }
  return result;
}


size_t findBelongingCentrePosition(const Instance &instance, const Dataset &centres) {
  assert(!centres.empty() && !instance.empty());
  size_t minDistClusterId = 0;
  double minDist = distanceSquared(instance, centres[0]);
  for(int i = 1; i < centres.size(); ++i) {
    double newDist = distanceSquared(instance, centres[i]);
    if(newDist < minDist) {
      minDist = newDist;
      minDistClusterId = i;
    }
  }
  return minDistClusterId;
}


Distance distanceToClosestCentre(const Instance &instance, const Dataset &centres) {
  assert(!centres.empty() && !instance.empty());
  return distanceSquared(centres[findBelongingCentrePosition(instance, centres)], instance);
}


Distance dx(const Dataset &dataset, const Weights &weights, const Dataset &centres) {
  if(centres.size() < 1 || dataset.size() != weights.size()) {
    return -1;
  }
  double result = 0;
  for(int i = 0; i < dataset.size(); ++i) {
    result += distanceToClosestCentre(dataset[i], centres) * weights[i];
  }
  return result;
}


bool prepareForClustering(const Dataset &dataset, const Weights &weights, const ull &k, Dataset &centres) {
  if(dataset.empty()) {
    std::cout << "Fatal error: Cannot cluster data with empty dataset." << std::endl;
  }
  if(dataset.size() < k) {
    std::cout << "Fatal error: Cannot cluster data with with  dataset of size less than k." << std::endl;
    std::cout << "dataset size: " << dataset.size() << ", k: " << k << std::endl;
    return false;
  }
  if(k < 1) {
    std::cout << "Fatal error: Cannot cluster data with less than 1 clusters." << std::endl;
    return false;
  }
  if(weights.size() != dataset.size()) {
    std::cout << "Fatal error: Number of weights does not match number of instances provided." << std::endl;
    return false;
  }

  //check that the dataset_ is all of the same size
  if(!analyzeDataset(dataset)) {
    std::cout << "Fatal error: Cannot cluster data that is not consistent in dimentianality of instances." << std::endl;
    return false;
  }

  int m = dataset[0].size(); //size of each instance in the dataset_;s

  //resizing the centres vector to the right size.  i.e. the given number k
  centres.resize(k);

  //resizing all of the centres to the right size;
  for(Instance i:centres) {
    i.resize(m);
  }
  return true;
}

}//namespace utils
}//namespace kmeans
