//
// Created by Yaser Alkayale on 2017-06-19.
//

#ifndef KMEANSII_KMEANSBASE_H
#define KMEANSII_KMEANSBASE_H


#include "kmeans_data.h"
#include "seed_picker_base.h"
#include "kmeans_helpers.h"
#include "iteration_runner_base.h"

namespace kmeans{
class KmeansBase{
protected:
  ull num_iterations_ = 0;
  ull iteration_runner_time_ = 0;
  ull seed_picker_time_ = 0;
  Distance distance_squared_ = 0;
  SeedPicker *seedPicker;
  IterationRunner *iterationRunner;

public:
  virtual inline ~KmeansBase() {};

  inline Distance
  cluster(const Dataset &dataset, const ull &k, std::vector<Instance> &centres) {
    return cluster(dataset, Weights(dataset.size(), 1), k, centres);
  };

  inline ull numIterations() { return num_iterations_; };

  inline ull iterationRunnerTime() { return iteration_runner_time_; };

  inline ull seedPickerTime() { return seed_picker_time_; };

  inline Distance distanceSquared() { return distance_squared_; };

  inline void clearInstance() {
    num_iterations_ = 0;
    iteration_runner_time_ = 0;
    seed_picker_time_ = 0;
    distance_squared_ = 0;
  };

  void pickSeeds(const Dataset &dataset, const Weights &weights, const ull &k, std::vector<Instance> &centres);
  void runIterations(const Dataset &dataset, const Weights &weights, std::vector<Instance> &centres);
  Distance cluster(const Dataset &dataset, const Weights &weights, const ull &k, std::vector<Instance> &centres);
};
}//namespace kmeans

#endif //KMEANSII_KMEANSBASE_H
