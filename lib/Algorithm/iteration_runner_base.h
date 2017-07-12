//
// Created by Yaser Alkayale on 2017-07-07.
//

#ifndef KMEANSII_ITERATIONRUNNERBASE_HH
#define KMEANSII_ITERATIONRUNNERBASE_HH

#include "kmeans_data.h"

namespace kmeans{
class IterationRunner{
public:
  virtual Distance
  runIterations(const Dataset &, const Weights &, Dataset &)=0;


  inline ull numIterations(){ return num_iterations_; };
protected:
  ull num_iterations_ = 0;
  Dataset dataset_;
  Weights weights_;
  Dataset centres_;
};
} //namespace kmeans
#endif //KMEANSII_ITERATIONRUNNERBASE_HH
