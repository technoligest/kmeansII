//
// Created by Yaser Alkayale on 2017-07-07.
//

#include "LloydIterationRunner.hh"
#include <cassert>
#include <cmath>
#include "KmeansHelpers.hh"

namespace LloydIterationHelpers{
 void operator/=(KmeansData::Instance &v, const vector<size_t> &d){
   std::cout<<"V size: "<<v.size()<<", d size: "<<d.size()<<endl;
   assert(v.size() == d.size());
   for(int i = 0; i < v.size(); ++i){
     v[i] /= d[i];
   }
 }
 void operator+=(KmeansData::Instance &v, const KmeansData::Instance &d){
   assert(v.size()==d.size());
   for(int i=0; i<v.size(); ++i){
     v[i]+=d[i];
   }
 }
}
KmeansData::dist LloydIterationRunner::runLloydIteration(){
  if(dataset.empty() || centres.empty() || dataset.size() < centres.size()){
    return -1;
  }

  KmeansData::dist totalDistance = 0;
  std::vector<KmeansData::Instance> newCentres(centres.size());
  std::vector<size_t> newCentreSizes(centres.size());

  //resetting all the values
  std::fill(newCentreSizes.begin(), newCentreSizes.end(), 0);
  for(auto &centre:newCentres){
    centre.resize(centres[0].size());
    std::fill(centre.begin(), centre.end(), 0);
  }

  totalDistance = calculateBelongings(newCentres, newCentreSizes);
  recalculateCentres(newCentres, newCentreSizes);
  centres = newCentres;

  return totalDistance;
}

KmeansData::dist LloydIterationRunner::runIterations(){
  if(dataset.empty() || centres.empty() || dataset.size() < centres.size()){
    return -1;
  }

  std::vector<KmeansData::Instance> bestCentres;

  double currDistance = std::numeric_limits<double>::max();
  double bestDistance = std::numeric_limits<double>::max();
  int iteration;
  for(iteration = 0; iteration < MAX_NUM_ITERATIONS; ++iteration){

    double newDistance = runLloydIteration();
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



/*
 * Here we are given a vecotor of instances
 */
void LloydIterationRunner::recalculateCentres(std::vector<KmeansData::Instance> newCentres,
                                         const std::vector<size_t> newCentreSizes){
  for(auto &centre: newCentres){
    centre /= newCentreSizes;
  }
}


KmeansData::dist LloydIterationRunner::calculateBelongings(KmeansData::Dataset newCentres, vector<size_t> newCentreSizes){
  size_t m = centres[0].size();
  KmeansData::dist totalDistance = 0;

  //adding each instance to where it belongs
  for(int instId = 0; instId < dataset.size(); ++instId){
    const KmeansData::Instance &inst = dataset[instId];
    auto minDistClusterId = KmeansHelpers::findBelongingCentrePosition(inst, centres);
    assert(newCentres[minDistClusterId].size() == m);
    newCentres[minDistClusterId] += inst;
    newCentreSizes[minDistClusterId] += weights[instId];
    totalDistance += KmeansHelpers::findDistanceSquared(inst,centres[minDistClusterId]);
  }
  return totalDistance;
}