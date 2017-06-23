/*
 * Created by Yaser Alkayale on 2017-06-22.
 *
 *
 *
 */


#ifndef KMEANSII_KMEANSINITIALIZER_HH
#define KMEANSII_KMEANSINITIALIZER_HH

#include <iostream>
#include "KmeansBase.hh"
#include "KmeansHelpers.hh"
#include "../handlers/data.hh"

template<class SP, class IR>
class KmeansInitializer : public KmeansBase {
public:
  inline KmeansInitializer() {};


  inline double cluster(const Dataset &d, std::vector<Instance> &centres, const Weights &weights, ull k) override {
    using namespace std;
    if (!KmeansHelpers::prepareForClustering(d, centres, weights, k)) {
      return -1;
    }
    SP s;

    //set random centres from the given dataset
    if (!s.pickSeeds(d, centres, weights, k)) {
      cout << "Could not generate random centres" << endl;
      return -1;
    }

    IR r;
    cout << "Started running iterations." << endl;
    auto result = r.runIterations(d, centres, weights);
    cout << "ended running the iterations" << endl;
    return result;
  }

  inline double cluster(const Dataset &d, std::vector<Instance> &centres, ull k) override {
    Weights weights(d.size());
    std::fill(weights.begin(), weights.end(), 1);
    return cluster(d, centres, weights, k);
  };
};




#endif //KMEANSII_KMEANSINITIALIZER_HH
