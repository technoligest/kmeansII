/*
 * Created by Yaser Alkayale on 2017-06-22.
 *
 *
 *
 */


#ifndef KMEANSII_KMEANSINSTANCE_HH
#define KMEANSII_KMEANSINSTANCE_HH

//
// Created by Yaser Alkayale on 2017-06-22.
//
#include <iostream>
#include "KmeansBase.hh"
#include "KmeansHelpers.hh"
#include "../handlers/data.hh"

template<class SP, class IR>
class KmeansInstance : public KmeansBase{
public:
  inline KmeansInstance(){};


  inline dist cluster(const Dataset &d, std::vector<Instance> &centres, const Weights &weights, ull k) override{
    using namespace std;
    if(!KmeansHelpers::prepareForClustering(d, centres, weights, k)){
      return -1;
    }
    clearInstance();
    SP s;
    ull startTime = static_cast<ull>(time(nullptr));
    //set random centres from the given dataset
    if(!s.pickSeeds(d, centres, weights, k)){
      cout << "Could not generate random centres" << endl;
      return -1;
    }
    _seedPickerTime = static_cast<ull>(time(nullptr)) - startTime;

    IR r;
    cout << "Started running iterations." << endl;
    startTime = static_cast<ull>(time(nullptr));

    auto result = r.runIterations(d, centres, weights);

    _iterationRunnerTime = static_cast<ull>(time(nullptr)) - startTime;
    cout << "ended running the iterations" << endl;

    _numIterations = r.numIterations();
    _distanceSquared = result;
    //std::cout << "YOLO" << endl;
    //std::cout << _seedPickerTime << endl;
    //std::cout << _numIterations << endl;
    //std::cout << _iterationRunnerTime << endl;
    //std::cout << _distanceSquared << endl;
    //cout << "EndYOLO" << endl;
    return result;
  }

  inline dist cluster(const Dataset &d, std::vector<Instance> &centres, ull k) override{
    Weights weights(d.size());
    std::fill(weights.begin(), weights.end(), 1);
    return cluster(d, centres, weights, k);
  };
};


#endif //KMEANSII_KMEANSIIINITIALIZER_HH




