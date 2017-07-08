//
// Created by Yaser Alkayale on 2017-06-19.
//

#ifndef KMEANSII_ITERATIONRUNNERS_H
#define KMEANSII_ITERATIONRUNNERS_H


#include "../handlers/data.hh"

class IterationRunner {
public:
  inline virtual KmeansData::dist
  runIterations(const KmeansData::Dataset &, KmeansData::Dataset &, const KmeansData::Weights &)=0;

  inline ull numIterations() { return _numIterations; };
protected:
  ull _numIterations = 0;
};


class LloydsIteration : public IterationRunner {
private:
  KmeansData::Dataset dataset;
  KmeansData::Weights weights;
  KmeansData::Dataset centres;

  //returns the sum of squared distances of all the pointst to their nearest clsuter centre
  KmeansData::dist runLloydIteration();
  KmeansData::dist runIterations();

  void recalculateCentres(KmeansData::Dataset newCentres, const vector<size_t> newCentreSizes);
  KmeansData::dist calculateBelongings(KmeansData::Dataset newCentres, vector<size_t> newCentreSizes);

public:
  //runs all the necessary iterations to complete the clustering
  //returns the total distance squared of the best iteration
  inline KmeansData::dist
  runIterations(const KmeansData::Dataset &d, KmeansData::Dataset &c, const KmeansData::Weights &w) override{
    dataset = d;
    weights = w;
    centres = c;
    runIterations();
  };

};

#endif //KMEANSII_ITERATIONRUNNERS_H
