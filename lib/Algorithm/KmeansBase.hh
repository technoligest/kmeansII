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
  KmeansData::dist _distanceSquared = 0;

public:
  inline ~KmeansBase(){};

  virtual KmeansData::dist cluster(const KmeansData::Dataset &, KmeansData::Dataset &, ull)=0;

  virtual KmeansData::dist cluster(const KmeansData::Dataset &, KmeansData::Dataset &, const KmeansData::Weights &, ull)=0;

  inline ull numIterations(){ return _numIterations; };

  inline ull iterationRunnerTime(){ return _iterationRunnerTime; };

  inline ull seedPickerTime(){ return _seedPickerTime; };

  inline KmeansData::dist distanceSquared(){ return _distanceSquared; };

  inline void clearInstance(){
    _numIterations = 0;
    _iterationRunnerTime = 0;
    _seedPickerTime = 0;
    _distanceSquared = 0;
  };
};


#endif //KMEANSII_KMEANSBASE_H
