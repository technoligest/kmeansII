//
// Created by Yaser Alkayale on 2017-06-19.
//

#ifndef KMEANSII_SEEDPICKERS_H
#define KMEANSII_SEEDPICKERS_H

#include <random>
#include <cassert>
#include <vector>
#include "kmeans_data.h"
#include "seed_picker_base.h"
#include "kmeans_helpers.h"
#include "kmeans_base.h"
#include "kmeans_instance.h"

namespace kmeans{

class RandomSeedPicker : public SeedPicker{
public:
  inline explicit RandomSeedPicker(){}

  bool pickSeeds(const Dataset &d, const Weights &weights, ull k, Dataset &centres) override;
};


class KmeansppSeedPicker : public SeedPicker{
public:
  inline explicit KmeansppSeedPicker(){}

  bool pickSeeds(const Dataset &d, const Weights &weights, ull k, Dataset &centres) override;
};

template<class IR>
class KmeansIISeedPicker : public SeedPicker{
public:
  inline explicit KmeansIISeedPicker(double _l, ull _r) : l_(_l), r_(_r){}

  bool pickSeeds(const Dataset &dataset, const Weights &weights, ull k, Dataset &centres) override;

private:
  double l_;  //input parameter as per the algorithm
  ull r_;     //input parameter as per the algorithm
};

//definition of this class is included here because it is mandatory since it is a templated class.
template<class IR>
bool KmeansIISeedPicker<IR>::pickSeeds(const Dataset &dataset, const Weights &weights, ull k, Dataset &centres) {
  std::cout << "Started picking seeds for KmeansII" << std::endl;
  if(dataset.empty() || dataset.size() < k) {
    return false;
  }

  size_t n = dataset.size(); //number of point in the dataset_

  //initializing random distribution
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(0, 1);

  std::vector<Instance> tempCentres;
  tempCentres.push_back(dataset[static_cast<int>((dis(gen) * n))]);
  double dx = helpers::calcDX(dataset, weights, tempCentres);

  ll passes = (r_ == -1) ? (static_cast<int>( log(dx) / log(2))) : r_;
  for(ll i = 0; i < passes; ++i){
    dx = helpers::calcDX(dataset, weights, tempCentres);
    for(int instId = 0; instId < dataset.size(); ++instId) {
      Instance inst = dataset[instId];
      size_t belongingCentreId = helpers::findBelongingCentrePosition(inst, tempCentres);
      double probability = l_ * helpers::findDistanceSquared(tempCentres[belongingCentreId], inst) / dx * weights[instId];
      double ran = static_cast<double>(dis(gen));
      if(ran <= probability){
        tempCentres.push_back(inst);
      }
    }
  }

  std::cout << "completed all the passes. " << std::endl;
  Weights tempWeights(tempCentres.size(), 0);
  for(size_t instId = 0; instId < dataset.size(); ++instId) {
    tempWeights[helpers::findBelongingCentrePosition(dataset[instId], tempCentres)] += weights[instId];
  }

  KmeansBase *kmeans = new KmeansInstance<KmeansppSeedPicker, IR>();
  kmeans->cluster(tempCentres, tempWeights, k, centres);
  delete kmeans;

  return true;
};
} //namspace kmeans


#endif //KMEANSII_SEEDPICKERS_H
