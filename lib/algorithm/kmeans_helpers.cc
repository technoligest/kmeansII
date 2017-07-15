//
// Created by Yaser Alkayale on 2017-07-12.
//


#include "kmeans_data.h"
#include <cassert>
#include <cmath>

namespace kmeans{
namespace helpers{

bool analyzeDataset(const Dataset &dataset){
  for(Instance i:dataset){
    if(i.size() != dataset[0].size()){
      return false;
    }
  }
  return true;
}

Distance findDistanceSquared(const Instance &instance1, const Instance &instance2){
  if(instance1.size() != instance2.size())
    return -1;
  Distance result = 0;
  size_t size = instance1.size();
  for(int i = 0; i < size; ++i){
    result += pow(instance1[i] - instance2[i], 2);
  }
  return result;
}

size_t findBelongingCentrePosition(const Instance &instance, const Dataset &centres){
  assert(!centres.empty() && !instance.empty());
  size_t minDistClusterId = 0;
  double minDist = findDistanceSquared(instance, centres[0]);
  for(int i = 1; i < centres.size(); ++i){
    double newDist = findDistanceSquared(instance, centres[i]);
    if(newDist < minDist){
      minDist = newDist;
      minDistClusterId = i;
    }
  }
  return minDistClusterId;
}

Distance shortestDistanceToClusterCentre(const Instance &instance, const Dataset &centres){
  assert(!centres.empty() && !instance.empty());
  return findDistanceSquared(centres[findBelongingCentrePosition(instance, centres)], instance);
}

Distance calcDX(const Dataset &dataset, const Weights &weights, const Dataset &centres){
  if(centres.size() < 1 || dataset.size() != weights.size()){
    return -1;
  }
  double result = 0;
  for(int i = 0; i < dataset.size(); ++i){
    result += shortestDistanceToClusterCentre(dataset[i], centres) * weights[i];
  }
  return result;
}

bool prepareForClustering(const Dataset &dataset, const Weights &weights, const ull &k, Dataset &centres){
  if(dataset.empty() || dataset.size() < k || k < 1){
    std::cout << "Cannot cluster data with empty dataset_ or one with too few values of k values of less than 1."
              << std::endl;
    return false;
  }
  if(weights.size() != dataset.size()){
    std::cout << "Number of weights does not match number of instances provided." << std::endl;
    return false;
  }

  //check that the dataset_ is all of the same size
  if(!analyzeDataset(dataset)){
    std::cout << "cannot cluster data that is not consistent." << std::endl;
    return false;
  }

  int m = dataset[0].size(); //size of each instance in the dataset_;s

  //resizing the centres vector to the right size.  i.e. the given number k
  centres.resize(k);

  //resizing all of the centres to the right size;
  for(Instance i:centres){
    i.resize(m);
  }
  return true;
}
}//namespace helpers
}//namespace kmeans
