//
// Created by Yaser Alkayale on 2017-06-22.
//

#ifndef KMEANSII_KMEANSINITIALIZER_HH
#define KMEANSII_KMEANSINITIALIZER_HH

#include <iostream>
#include "KmeansBase.hh"
#include "KmeansHelpers.hh"
#include "SeedPickers.hh"
#include "IterationRunners.hh"
#include "../handlers/data.hh"
template<class SP, class IR>
class KmeansInitializer : public KmeansBase {
public:
  inline KmeansInitializer() {};

  inline double cluster(const Dataset &d, std::vector<Instance> &centres, const Weights &weights, ull k) override {
    if (!KmeansHelpers::prepareForClustering(d, centres, weights, k)) {
      return -1;
    }
    SP s;
    //set random centres from the given dataset
    if (!s.pickSeeds(d, centres, weights, k)) {
      std::cout << "Could not generate random centres";
      return -1;
    }
    IR r;
    return r.runIterations(d, centres, weights);
  }

  inline double cluster(const Dataset &d, std::vector<Instance> &centres, ull k) override {
    Weights weights(d.size());
    std::fill(weights.begin(), weights.end(), 1);
    return cluster(d, centres, weights, k);
  };
};


#endif //KMEANSII_KMEANSINITIALIZER_HH
