//
// Created by Yaser Alkayale on 2017-07-11.
//
#include "kmeans_base.h"
#include "kmeans_io.h"
#include "globals.h"
#include <cassert>
#include <chrono>

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
#ifdef DEBUG_KMEANS
  std::cout << "Done clustering." << std::endl << std::endl << std::endl;
#endif
  return distance_squared_;
}

/*
 * Pick seeds using the already passed seedPicker_. The seedPicker_ is a attribute of the class.
 */
void
KmeansBase::pickSeeds(const Dataset &dataset, const Weights &weights, const ull &k, std::vector<Instance> &centres) {
#ifdef DEBUG_KMEANS
  std::cout << "Started picking seeds using " << seedPicker_->name() << std::endl;
#endif
  auto startTime = std::chrono::high_resolution_clock::now();
  assert(seedPicker_->pickSeeds(dataset, weights, k, centres));
  auto finishTime = std::chrono::high_resolution_clock::now();
  seed_picker_time_ = std::chrono::duration_cast<std::chrono::nanoseconds>(finishTime-startTime).count();

#ifdef DEBUG_KMEANS
  std::cout << "Finished picking seeds using " << seedPicker_->name() << std::endl;
#endif
}

/*
 * Run the iterations using the iterationRunner_ provided in the class.
 */
void KmeansBase::runIterations(const Dataset &dataset, const Weights &weights, std::vector<Instance> &centres) {
#ifdef DEBUG_KMEANS
  std::cout << "Started running iterations using " << iterationRunner_->name() << std::endl;
#endif
  auto startTime = std::chrono::high_resolution_clock::now();
  distance_squared_ = iterationRunner_->runIterations(dataset, weights, centres);
  auto finishTime = std::chrono::high_resolution_clock::now();
  iteration_runner_time_ = std::chrono::duration_cast<std::chrono::nanoseconds>(finishTime-startTime).count();
  num_iterations_ = iterationRunner_->numIterations();
#ifdef DEBUG_KMEANS
  std::cout << "ended running the iterations" << iterationRunner_->name() << std::endl;
#endif
}

void KmeansBase::print(std::ostream &out) {
  assert (seed_picker_time_ >= 0);
  out << ">>>Start Experiment" << std::endl;
  out << "Seed Picker: " << seedPicker_->name() << std::endl;
  out << "Iteration runne: " << iterationRunner_->name() << std::endl;
  out << "Sum of distance squared to centre: " << distance_squared_ << std::endl;
  out << "Time to pick the seeds: " << seed_picker_time_ << std::endl;
  out << "Number of iterations run: " << num_iterations_ << std::endl;
  out << "Time to run the iterations: " << iteration_runner_time_ << std::endl;
  out << "Start Centres:" << std::endl;
  out << centres_ << std::endl;
  out << "End Centres:" << std::endl;
  out << "End Experiment:" << std::endl;
}

}//namespace kmeans;
