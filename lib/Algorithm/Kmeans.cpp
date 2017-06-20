//
// Created by Yaser Alkayale on 2017-05-29.
//

#include "Kmeans.h"

//template<class SeedPicker, class IterationRunner>
//KmeansInitializer<SeedPicker,IterationRunner>::KmeansInitializer(){}

template<class SeedPicker, class IterationRunner>
//function returns the sum of squared distance of the centroids it finds.
double KmeansInitializer<SeedPicker, IterationRunner>::cluster(const Dataset &d, std::vector<Instance> &centres, const Weights &weights, ull k) {
  if (!KmeansHelpers::prepareForClustering(d, centres, weights, k)) {
    return -1;
  }
  SeedPicker s;
  //set random centres from the given dataset
  if (!s.pickSeeds(d, centres, weights, k)) {
    std::cout << "Could not generate random centres";
    return -1;
  }
  IterationRunner r;
  return r.runIterations(d, centres, weights);
}

template<class SeedPicker, class IterationRunner>
double KmeansInitializer<SeedPicker, IterationRunner>::cluster(const Dataset &d, std::vector<Instance> &centres, ull k) {
  Weights weights(d.size());
  std::fill(weights.begin(), weights.end(), 1);
  return cluster(d, centres, weights, k);
}


