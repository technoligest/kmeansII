//
// Created by Yaser Alkayale on 2017-07-07.
//

#ifndef KMEANSII_ITERATIONRUNNERBASE_HH
#define KMEANSII_ITERATIONRUNNERBASE_HH

#include "kmeans_data.h"

namespace kmeans{

class IterationRunner{
public:
  virtual Distance runIterations(const Dataset &, const Weights &, Dataset &)=0;
  inline ull numIterations(){ return num_iterations_; };
  virtual inline ~IterationRunner(){}
protected:
  ull num_iterations_ = 0;
};

} //namespace kmeans
#endif //KMEANSII_ITERATIONRUNNERBASE_HH
