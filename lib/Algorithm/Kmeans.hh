//
// Created by Yaser Alkayale on 2017-05-29.
//

#ifndef KMEANSII_KMEANS_H
#define KMEANSII_KMEANS_H

#include "../handlers/data.hh"
#include "KmeansBase.hh"
#include "KmeansHelpers.hh"
#include "SeedPickers.hh"

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



//IR = iterationRunner

template<class IR>
using Kmeans = KmeansInitializer<RandomSeedPicker,IR>;

template <class IR>
using Kmeanspp = KmeansInitializer<KmeansppSeedPicker, IR>;

template<typename InnerIR, typename OuterIR>
using KmeansII = KmeansInitializer<KmeansIISeedPicker<InnerIR>,OuterIR>;



#endif //KMEANSII_KMEANS_H

