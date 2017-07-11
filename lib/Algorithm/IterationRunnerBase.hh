//
// Created by Yaser Alkayale on 2017-07-07.
//

#ifndef KMEANSII_ITERATIONRUNNERBASE_HH
#define KMEANSII_ITERATIONRUNNERBASE_HH

#include "../handlers/data.hh"

class IterationRunner {
public:
  inline virtual KmeansData::dist
  runIterations(const KmeansData::Dataset &, KmeansData::Dataset &, const KmeansData::Weights &)=0;

  inline ull numIterations() { return _numIterations; };
protected:
  ull _numIterations = 0;
};
#endif //KMEANSII_ITERATIONRUNNERBASE_HH
