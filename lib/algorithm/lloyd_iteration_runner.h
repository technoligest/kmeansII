//
// Created by Yaser Alkayale on 2017-07-07.
//

#ifndef KMEANSII_LLOYDITERATIONRUNNER_HH
#define KMEANSII_LLOYDITERATIONRUNNER_HH


#include <cassert>
#include "iteration_runner_base.h"
#include "kmeans_utils.h"

namespace kmeans{
class LloydIterationRunner : public IterationRunner{
private:
  //returns the sum of squared distances of all the pointst to their nearest clsuter centre
  Distance runLloydIteration(const Dataset &dataset, const Weights &weights, Dataset &centres);
  Distance runLloydIterations(const Dataset &dataset, const Weights &weights, Dataset &centres);
  ull maxNumIterations_;
  const static std::string name_;

public:
  //runs all the necessary iterations to complete the clustering
  //returns the total distance squared of the best iteration
  //assumes the centres given are of the right size (i.e. k)
  inline Distance runIterations(const Dataset &dataset, const Weights &weights, Dataset &centres) override {
    if(!utils::analyzeDataset(dataset) || !utils::analyzeDataset(centres)) { return -1; }
    num_iterations_ = 0;
    return runLloydIterations(dataset, weights, centres);
  };
  inline explicit LloydIterationRunner(ull maxNumIterations = 200):maxNumIterations_(maxNumIterations){}
  inline std::string name() override {return name_;}
};
} // namespace kmeans
#endif //KMEANSII_LLOYDITERATIONRUNNER_HH
