//
// Created by Yaser Alkayale on 2017-06-19.
//

#ifndef KMEANSII_KMEANSBASE_H
#define KMEANSII_KMEANSBASE_H


#include "data.hh"
#include "SeedPickerBase.hh"
#include "KmeansHelpers.hh"
#include "IterationRunnerBase.hh"

namespace kmeans{
class KmeansBase{
protected:
  ull _numIterations = 0;
  ull _iterationRunnerTime = 0;
  ull _seedPickerTime = 0;
  dist _distanceSquared = 0;
  SeedPicker *sp;
  IterationRunner *ir;

public:
  inline ~KmeansBase(){
    delete sp;
    delete ir;
  };

  inline dist
  cluster(const Dataset &d, std::vector<Instance> &centres, ull k){
    return cluster(d, centres, Weights(d.size(), 1), k);
  };

  inline ull numIterations(){ return _numIterations; };

  inline ull iterationRunnerTime(){ return _iterationRunnerTime; };

  inline ull seedPickerTime(){ return _seedPickerTime; };

  inline dist distanceSquared(){ return _distanceSquared; };

  inline void clearInstance(){
    _numIterations = 0;
    _iterationRunnerTime = 0;
    _seedPickerTime = 0;
    _distanceSquared = 0;
  };

  void pickSeeds(const Dataset &, std::vector<Instance> &, const Weights &, ull);
  void runIterations(const Dataset &dataset, std::vector<Instance> &centres, const Weights &weights);
  dist cluster(const Dataset &, std::vector<Instance> &, const Weights &, ull);
};
}//namespace kmeans

#endif //KMEANSII_KMEANSBASE_H
