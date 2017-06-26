//
// Created by Yaser Alkayale on 2017-06-22.
//

#ifndef KMEANSII_KMEANSIIINITIALIZER_HH
#define KMEANSII_KMEANSIIINITIALIZER_HH
#include "SeedPickers.hh"

template<class InnerIR,class OuterIR>
class KmeansInstance<KmeansIISeedPicker<InnerIR>,OuterIR>: public KmeansBase{
private:
  double l;
public:
  inline KmeansInstance(double _l):l(_l){};


  inline double cluster(const Dataset &d, std::vector<Instance> &centres, const Weights &weights, ull k)  {
    using namespace std;
    if (!KmeansHelpers::prepareForClustering(d, centres, weights, k)) {
      return -1;
    }
    KmeansIISeedPicker<InnerIR> s(l);

    //set random centres from the given dataset
    if (!s.pickSeeds(d, centres, weights, k)) {
      cout << "Could not generate random centres" << endl;
      return -1;
    }

    OuterIR r;
    cout << "Started running iterations." << endl;
    auto result = r.runIterations(d, centres, weights);
    cout << "ended running the iterations" << endl;
    return result;
  }

  inline double cluster(const Dataset &d, std::vector<Instance> &centres, ull k){
    Weights weights(d.size());
    std::fill(weights.begin(), weights.end(), 1);
    return cluster(d, centres, weights, k);
  };
};
#endif //KMEANSII_KMEANSIIINITIALIZER_HH
