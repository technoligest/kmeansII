//
// Created by Yaser Alkayale on 2017-06-21.
//
#include "IterationRunners.hh"
#include <cassert>
#include <cmath>
#include "KmeansHelpers.hh"

using namespace KmeansHelpers;

double LloydsIteration::runLloydIteration(const Dataset &d, std::vector<Instance> &centres, const Weights &weights){
  if(d.empty() || centres.empty() || d.size() < centres.size()){
    return -1;
  }

  double totalDistance = 0;
  size_t n = d.size();           //the number of items in the dataset
  size_t k = centres.size();     //the number of clusters
  size_t m = centres[0].size();  //the size of each row

  std::vector<Instance> newCentres(k);
  std::vector<size_t> newCentreSizes(k);

  //resetting all the values
  std::fill(newCentreSizes.begin(), newCentreSizes.end(), 0);
  for(auto &centre:newCentres){
    centre.resize(m);
    std::fill(centre.begin(), centre.end(), 0);
  }

  //adding each instance to where it belongs
  for(int instId = 0; instId < n; ++instId){
    const Instance &inst = d[instId];
    assert(centres.size() == k);
    int minDistClusterId = 0;
    double minDist = KmeansHelpers::findDistanceSquared(inst, centres[0]);
    for(int i = 1; i < k; ++i){
      Instance &centre = centres[i];
      double newDist = KmeansHelpers::findDistanceSquared(inst, centre) * weights[instId];
      if(newDist < minDist){
        minDist = newDist;
        minDistClusterId = i;
      }
    }
    assert(newCentres[minDistClusterId].size() == m);
    for(int i = 0; i < m; ++i){
      newCentres[minDistClusterId][i] += inst[i];
    }
    newCentreSizes[minDistClusterId] += weights[instId];
    totalDistance += minDist;
  }

  //recalculating the right centres
  for(int i = 0; i < k; ++i){
    auto &centre = newCentres[i];
    for(auto &point: centre){
      if(newCentreSizes[i] != 0){
        point /= newCentreSizes[i];
      }
    }
  }
  centres = newCentres;
  return totalDistance;
}

double LloydsIteration::runIterations(const Dataset &d, Dataset &centres, const Weights &weights){
  if(d.empty() || centres.empty() || d.size() < centres.size()){
    return -1;
  }

  std::vector<Instance> bestCentres;

  double currDistance = std::numeric_limits<double>::max();
  double bestDistance = std::numeric_limits<double>::max();
  int iteration;
  for(iteration = 0; iteration < MAX_NUM_ITERATIONS; ++iteration){

    double newDistance = runLloydIteration(d, centres, weights);
    if(newDistance < bestDistance){
      bestDistance = newDistance;
      bestCentres = centres;
    }
    if(newDistance > currDistance * LOCAL_ITERATION_BIAS){
      std::cout << "Terminating because iteration has exceeded local bias." << std::endl;
      break;
    }
    std::cout << "NewDist: "<< newDistance<<" CurrDist: " << currDistance << std::endl;
    if(fabs(newDistance - currDistance) < CONVERGENCE_THREASHOLD){
      std::cout << "Terminating because iterations are stable." << std::endl;
      break;
    }
    currDistance = newDistance;
  }
  std::cout << "numIterations: " << iteration << std::endl;
  _numIterations = iteration;
  return bestDistance;
}
