//
// Created by Yaser Alkayale on 2017-06-19.
//

#ifndef KMEANSII_KMEANSBASE_H
#define KMEANSII_KMEANSBASE_H


#include "../handlers/data.hh"

class KmeansBase{
protected:
  ull _numIterations = 0;
  ull _iterationRunnerTime = 0;
  ull _seedPickerTime = 0;
  dist _distanceSquared = 0;

public:
  inline ~KmeansBase(){};

  virtual dist cluster(const Dataset &, Dataset &, ull)=0;

  virtual dist cluster(const Dataset &, Dataset &, const Weights &, ull)=0;

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

};


#endif //KMEANSII_KMEANSBASE_H
