//
// Created by Yaser Alkayale on 2017-06-19.
//

#ifndef KMEANSII_ITERATIONRUNNERS_H
#define KMEANSII_ITERATIONRUNNERS_H


#include "../handlers/data.hh"

class IterationRunner {
public:
  inline virtual dist runIterations(const Dataset &, Dataset &, const Weights &)=0;

  inline ull numIterations() { return _numIterations; };
protected:
  ull _numIterations = 0;
};


class LloydsIteration : public IterationRunner {
private:
  //returns the sum of squared distances of all the pointst to their nearest clsuter centre
  dist runLloydIteration(const Dataset &d, std::vector<Instance> &centres, const Weights &weights);

public:
  //runs all the necessary iterations to complete the clustering
  //returns the total distance squared of the best iteration
  dist runIterations(const Dataset &d, Dataset &centres, const Weights &weights) override;
};

#endif //KMEANSII_ITERATIONRUNNERS_H
