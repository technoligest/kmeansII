//
// Created by Yaser Alkayale on 2017-06-27.
//

#ifndef KMEANSII_KMEANS2INSTANCE_HH
#define KMEANSII_KMEANS2INSTANCE_HH

#include "SeedPickers.hh"
#include "KmeansBase.hh"
#include "KmeansHelpers.hh"

template<class InnerIR,class OuterIR>
class KmeansInstance<KmeansIISeedPicker<InnerIR>,OuterIR>: public KmeansBase{
private:
  double l;
  ull r;
public:
  inline KmeansInstance(double _l, ull _r):l(_l),r(_r){};


  inline double
  cluster(const KmeansData::Dataset &d, KmeansData::Dataset &centres, const KmeansData::Weights &weights,
          ull k) override{
    using namespace std;
    if (!KmeansHelpers::prepareForClustering(d, centres, weights, k)) {
      return -1;
    }
    clearInstance();
    KmeansIISeedPicker<InnerIR> s(l,r);

    ull startTime = static_cast<ull>(time(nullptr));
    //set random centres from the given dataset
    if (!s.pickSeeds(d, centres, weights, k)) {
      cout << "Could not generate random centres" << endl;
      return -1;
    }
    _seedPickerTime = static_cast<ull>(time(nullptr)) - startTime;

    OuterIR r;
    cout << "Started running iterations." << endl;
    startTime = static_cast<ull>(time(nullptr));
    auto result = r.runIterations(d, centres, weights);
    _iterationRunnerTime = static_cast<ull>(time(nullptr)) - startTime;
    cout << "ended running the iterations" << endl;

    _numIterations = r.numIterations();
    _distanceSquared = result;
    return result;
  }

  inline double cluster(const KmeansData::Dataset &d, std::vector<KmeansData::Instance> &centres, ull k) override{
    KmeansData::Weights weights(d.size());
    std::fill(weights.begin(), weights.end(), 1);
    return cluster(d, centres, weights, k);
  };
};
#endif //KMEANSII_KMEANS2INSTANCE_HH
