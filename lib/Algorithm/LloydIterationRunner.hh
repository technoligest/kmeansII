//
// Created by Yaser Alkayale on 2017-07-07.
//

#ifndef KMEANSII_LLOYDITERATIONRUNNER_HH
#define KMEANSII_LLOYDITERATIONRUNNER_HH


#include "IterationRunnerBase.hh"
#include <cassert>

namespace kmeans{
class LloydIterationRunner : public IterationRunner{
private:

  //returns the sum of squared distances of all the pointst to their nearest clsuter centre
  dist runLloydIteration();
  dist runIterations();

  void recalculateCentres(Dataset newCentres, const std::vector<size_t> newCentreSizes);
  dist calculateBelongings(Dataset newCentres, std::vector<size_t> newCentreSizes);

  void divideAll(Instance &, const std::vector<size_t> &);
  void addAll(Instance &, const Instance &);

public:
  //runs all the necessary iterations to complete the clustering
  //returns the total distance squared of the best iteration
  inline dist
  runIterations(const Dataset &d, Dataset &c, const Weights &w) override{
    dataset = d;
    weights = w;
    centres = c;
    return runIterations();
  };
};
} // namespace kmeans
#endif //KMEANSII_LLOYDITERATIONRUNNER_HH
