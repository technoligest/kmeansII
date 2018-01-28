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
#include "kmeans_utils.h"
#include "kmeans_base.h"
#include "kmeans_instance.h"
#include "globals.h"

namespace kmeans{

class NewSeedPicker : public SeedPicker{
public:
  inline explicit NewSeedPicker(ull runs, ull iterations):runs_(runs),iterations_(iterations){}
  inline std::string name()override{return name_;}
  bool pickSeeds(const Dataset &d, const Weights &weights, ull k, Dataset &centres) override;

private:
  ull runs_;
  ull iterations_;
  const static std::string name_;
};

class RandomSeedPicker : public SeedPicker{
public:
  inline explicit RandomSeedPicker(){}
  inline std::string name()override{return name_;}
  bool pickSeeds(const Dataset &d, const Weights &weights, ull k, Dataset &centres) override;
private:
  const static std::string name_;
};


class KmeansppSeedPicker : public SeedPicker{
public:
  inline explicit KmeansppSeedPicker(){}
  inline std::string name()override{return name_;}
  bool pickSeeds(const Dataset &d, const Weights &weights, ull k, Dataset &centres) override;
private:
  const static std::string name_;
};

template<class IR>
class KmeansIISeedPicker : public SeedPicker{
public:
  inline explicit KmeansIISeedPicker(double _l, ull _r) : l_(_l), r_(_r){}
  inline std::string name(){return name_;}
  bool pickSeeds(const Dataset &dataset, const Weights &weights, ull k, Dataset &centres) override;

private:
  double l_;  //input parameter as per the algorithm
  ull r_;     //input parameter as per the algorithm
  const static std::string name_;
};

template<class IR>
const std::string KmeansIISeedPicker<IR>::name_ = std::string("Kmeans|| Seed Picker");

//definition of this class is included here because it is mandatory since it is a templated class.
template<class IR>
bool KmeansIISeedPicker<IR>::pickSeeds(const Dataset &dataset, const Weights &weights, ull k, Dataset &centres) {
#ifdef DEBUG
  std::cout << "Started picking seeds for KmeansII" << std::endl;
#endif
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
  double dx = utils::dx(dataset, weights, tempCentres);

  ll passes = (r_ == -1) ? (static_cast<int>( log(dx) / log(2))) : r_;
  for(ll i = 0; i < passes; ++i){
    dx = utils::dx(dataset, weights, tempCentres);
    for(int instId = 0; instId < dataset.size(); ++instId) {
      Instance inst = dataset[instId];
      size_t belongingCentreId = utils::findBelongingCentrePosition(inst, tempCentres);
      double probability = l_ * utils::distanceSquared(tempCentres[belongingCentreId], inst) / dx * weights[instId];
      double ran = static_cast<double>(dis(gen));
      if(ran <= probability){
        tempCentres.push_back(inst);
      }
    }
  }
#ifdef DEBUG
  std::cout << "completed all the passes. " << std::endl;
#endif //DEBUG
  Weights tempWeights(tempCentres.size(), 0);
  for(size_t instId = 0; instId < dataset.size(); ++instId) {
    tempWeights[utils::findBelongingCentrePosition(dataset[instId], tempCentres)] += weights[instId];
  }

  assert(tempCentres.size()>=k);
  KmeansBase *kmeans = new KmeansInstance<KmeansppSeedPicker, IR>();
  kmeans->cluster(tempCentres, tempWeights, k, centres);
  delete kmeans;

  return true;
};
} //namspace kmeans


#endif //KMEANSII_SEEDPICKERS_H
