//
// Created by Yaser Alkayale on 2017-07-11.
//
#include "kmeans_base.h"
#include <cassert>

namespace kmeans{
/*
 * Calculate the centres of a clustering and save them into centres.
 * This only works because centres is passed by reference.
 * return the total squared distance of the clustering
 */
Distance
KmeansBase::cluster(const Dataset &dataset, const Weights &weights, const ull &k, std::vector<Instance> &centres) {
  if(!utils::prepareForClustering(dataset, weights, k, centres)) { return -1; }
  clearInstance();
  pickSeeds(dataset, weights, k, centres);
  runIterations(dataset, weights, centres);
  return distance_squared_;
}

/*
 * Pick seeds using the already passed seedPicker. The seedPicker is a attribute of the class.
 */
void
KmeansBase::pickSeeds(const Dataset &dataset, const Weights &weights, const ull &k, std::vector<Instance> &centres) {
  ull startTime = static_cast<ull>(time(nullptr));
  assert(seedPicker->pickSeeds(dataset, weights, k, centres));
  seed_picker_time_ = static_cast<ull>(time(nullptr)) - startTime;
}

/*
 * Run the iterations using the iterationRunner provided in the class.
 */
void KmeansBase::runIterations(const Dataset &dataset, const Weights &weights, std::vector<Instance> &centres) {
#ifdef DEBUG
  std::cout << "Started running iterations." << std::endl;
#endif
  ull startTime = static_cast<ull>(time(nullptr));
  distance_squared_ = iterationRunner->runIterations(dataset, weights, centres);
  iteration_runner_time_ = static_cast<ull>(time(nullptr)) - startTime;
  num_iterations_ = iterationRunner->numIterations();
#ifdef DEBUG
  std::cout << "ended running the iterations" << std::endl;
#endif
}

}//namespace kmeans;
