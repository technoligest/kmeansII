//
// Created by Yaser Alkayale on 2017-07-11.
//
#include "kmeans_base.h"
#include <cassert>

namespace kmeans{


Distance
KmeansBase::cluster(const Dataset &dataset, const Weights &weights, const ull &k, std::vector<Instance> &centres) {
  if(!helpers::prepareForClustering(dataset, weights, k, centres)) { return -1; }
  clearInstance();
  pickSeeds(dataset, weights, k, centres);

  runIterations(dataset, weights, centres);
  return distance_squared_;
}

void
KmeansBase::pickSeeds(const Dataset &dataset, const Weights &weights, const ull &k, std::vector<Instance> &centres) {
//set random centres from the given dataset_
  ull startTime = static_cast<ull>(time(nullptr));
  assert(seed_picker_->pickSeeds(dataset, weights, k, centres));
  seed_picker_time_ = static_cast<ull>(time(nullptr)) - startTime;
}

void KmeansBase::runIterations(const Dataset &dataset, const Weights &weights, std::vector<Instance> &centres) {
  std::cout << "Started running iterations." << std::endl;
  ull startTime = static_cast<ull>(time(nullptr));
  distance_squared_ = iteration_runner_->runIterations(dataset, weights, centres);
  iteration_runner_time_ = static_cast<ull>(time(nullptr)) - startTime;
  std::cout << "ended running the iterations" << std::endl;
  num_iterations_ = iteration_runner_->numIterations();
}

}//namespace kmeans;
