//
// Created by Yaser Alkayale on 2017-07-07.
//

#ifndef KMEANSII_ITERATIONRUNNERBASE_HH
#define KMEANSII_ITERATIONRUNNERBASE_HH

#include "data.hh"

namespace kmeans{
class IterationRunner{
public:
  virtual dist
  runIterations(const Dataset &d, Dataset &c, const Weights &w)=0;


  inline ull numIterations(){ return _numIterations; };
protected:
  ull _numIterations = 0;
  Dataset dataset;
  Weights weights;
  Dataset centres;
};
} //namespace kmeans
#endif //KMEANSII_ITERATIONRUNNERBASE_HH
