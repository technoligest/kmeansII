//
// Created by Yaser Alkayale on 2017-07-11.
//
#include "KmeansBase.hh"
namespace kmeans{
dist
KmeansBase::cluster(const Dataset &dataset, std::vector<Instance> &centres, const Weights &weights, ull k){
  if(!helpers::prepareForClustering(dataset, centres, weights, k)){ return -1; }
  clearInstance();
  pickSeeds(dataset,centres,weights,k);
  runIterations(dataset,centres,weights);

  return _distanceSquared;
}


void KmeansBase::pickSeeds(const Dataset &dataset, std::vector<Instance> &centres, const Weights &weights, ull k){
//set random centres from the given dataset
  ull startTime = static_cast<ull>(time(nullptr));
  assert(sp->pickSeeds(dataset, centres, weights, k));
  _seedPickerTime = static_cast<ull>(time(nullptr)) - startTime;
}

void KmeansBase::runIterations(const Dataset &dataset, std::vector<Instance> &centres, const Weights &weights){
  std::cout << "Started running iterations." << std::endl;
  ull startTime = static_cast<ull>(time(nullptr));
  _distanceSquared = ir->runIterations(dataset,centres,weights);
  _iterationRunnerTime = static_cast<ull>(time(nullptr)) - startTime;
  std::cout << "ended running the iterations" << std::endl;
  _numIterations = ir->numIterations();
}
}//namespace kmeans;
