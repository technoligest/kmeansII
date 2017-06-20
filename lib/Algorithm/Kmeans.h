//
// Created by Yaser Alkayale on 2017-05-29.
//

#ifndef KMEANSII_KMEANS_H
#define KMEANSII_KMEANS_H

#include "../handlers/data.h"
#include "SeedPickers.h"
#include "KmeansBase.h"

template<class SeedPicker, class IterationRunner>
class KmeansInitializer : public KmeansBase {
public:
  inline KmeansInitializer(){};
  double cluster(const Dataset &, std::vector<Instance> &, ull);

  double cluster(const Dataset &, std::vector<Instance> &, const Weights &, ull);

};

//IR = iterationRunner

//template<class IR>
//using Kmeans = KmeansInitializer<RandomSeedPicker,IR>;
//
//template <class IR>
//using Kmeanspp = KmeansInitializer<KmeansppSeedPicker, IR>;

//template<typename InnerIR, typename OuterIR>
//using KmeansII = KmeansInitializer<KmeansIISeedPicker<InnerIR>,OuterIR>;



#endif //KMEANSII_KMEANS_H

