//
// Created by Yaser Alkayale on 2017-07-07.
//

#ifndef KMEANSII_LLOYDITERATIONRUNNER_HH
#define KMEANSII_LLOYDITERATIONRUNNER_HH


#include <cassert>
#include "iteration_runner_base.h"

namespace kmeans{
class LloydIterationRunner : public IterationRunner{
private:

  //returns the sum of squared distances of all the pointst to their nearest clsuter centre
  Distance runLloydIteration();
  Distance runIterations();

  void recalculateCentres(const std::vector<size_t> newCentreSizes, Dataset newCentres);
  Distance calculateBelongings(std::vector<size_t> newCentreSizes, Dataset newCentres);


public:
  //runs all the necessary iterations to complete the clustering
  //returns the total distance squared of the best iteration
  inline Distance
  runIterations(const Dataset &d, const Weights &w, Dataset &c) override {
    dataset_ = d;
    weights_ = w;
    centres_ = c;
    return runIterations();
  };
};
} // namespace kmeans
#endif //KMEANSII_LLOYDITERATIONRUNNER_HH
