//
// Created by Yaser Alkayale on 2017-06-19.
//

#ifndef KMEANSII_KMEANSBASE_H
#define KMEANSII_KMEANSBASE_H


#include <cassert>
#include "kmeans_data.h"
#include "seed_picker_base.h"
#include "kmeans_utils.h"
#include "iteration_runner_base.h"
#include "globals.h"

namespace kmeans{
class KmeansBase{
protected:
  //Variables specific per clustering run. Need to be reset every clustering.
  ull num_iterations_ = 0;
  int iteration_runner_time_ = -1;
  int  seed_picker_time_ = -1;
  Distance distance_squared_ = 0; //Sum of distance square of each point to its cluster Centre
  Dataset centres_;

  //Variables constant for the class instance
  SeedPicker *seedPicker_;
  IterationRunner *iterationRunner_;

public:
  inline KmeansBase(IterationRunner *iterationRunner, SeedPicker *seedPicker) :
      seedPicker_(seedPicker), iterationRunner_(iterationRunner) {}
  virtual inline ~KmeansBase(){}

  inline Distance cluster(const Dataset &dataset, const ull &k, std::vector<Instance> &centres) {
    auto result = cluster(dataset, Weights(dataset.size(), 1), k, centres);
    centres_ = centres;
    return result;
  }

  inline ull numIterations() { return num_iterations_; }

  inline ull iterationRunnerTime() { return iteration_runner_time_; }

  inline ull seedPickerTime() { return seed_picker_time_; }

  inline Distance distanceSquared() { return distance_squared_; }

  inline void clearInstance() {
    num_iterations_ = 0;
    iteration_runner_time_ = 0;
    seed_picker_time_ = 0;
    distance_squared_ = 0;
    centres_ = Dataset();
  }

  void pickSeeds(const Dataset &dataset, const Weights &weights, const ull &k, std::vector<Instance> &centres);
  void runIterations(const Dataset &dataset, const Weights &weights, std::vector<Instance> &centres);
  Distance cluster(const Dataset &dataset, const Weights &weights, const ull &k, std::vector<Instance> &centres);
  void print(std::ostream &out);

};

}//namespace kmeans

#endif //KMEANSII_KMEANSBASE_H
