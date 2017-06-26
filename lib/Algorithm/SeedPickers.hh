//
// Created by Yaser Alkayale on 2017-06-19.
//

#ifndef KMEANSII_SEEDPICKERS_H
#define KMEANSII_SEEDPICKERS_H

#include <random>
#include <cassert>
#include <vector>
#include "../handlers/data.hh"
#include "KmeansHelpers.hh"
#include "KmeansInstance.hh"


class SeedPicker {
public:
  virtual bool pickSeeds(const Dataset &d, Dataset &centres, const Weights &weights, ull k)=0;
};


class RandomSeedPicker : public SeedPicker {
public:
  inline RandomSeedPicker() {}

  bool pickSeeds(const Dataset &d, Dataset &centres, const Weights &weights, ull k) override;
};


class KmeansppSeedPicker : public SeedPicker {
public:
  inline KmeansppSeedPicker() {}

  bool pickSeeds(const Dataset &d, Dataset &centres, const Weights &weights, ull k) override;
};

template<class IR>
class KmeansIISeedPicker : public SeedPicker {
public:
  inline KmeansIISeedPicker(double _l) : l(_l) {}

  bool pickSeeds(const Dataset &d, Dataset &centres, const Weights &weights, ull k) override;

private:
  double l;
};

//definition of this class is included here because it is mandatory since it is a templated class.
template<class IR>
bool KmeansIISeedPicker<IR>::pickSeeds(const Dataset &d, Dataset &centres, const Weights &weights, ull k) {
  std::cout << "Started picking seeds for KmeansII" << std::endl;
  if (d.empty() || centres.empty() || d.size() < k) {
    return false;
  }

  size_t n = d.size();

  //initializing random distribution
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(0, 1);


  std::vector<Instance> tempCentres;
  tempCentres.push_back(d[static_cast<int>((dis(gen) * n))]);
  double dx = KmeansHelpers::calcDX(d, tempCentres);
  ll passes = static_cast<int>( log(dx) / log(2));
  for (ll i = 0; i < passes; ++i) {
    dx = KmeansHelpers::calcDX(d, tempCentres);
    for (int instId = 0; instId < d.size(); ++instId) {
      Instance inst = d[instId];
      double probability = l * KmeansHelpers::shortestDistanceToClusterCentre(tempCentres, inst) / dx * weights[instId];
      double ran = static_cast<double>(dis(gen));
      if (ran <= probability) {
        tempCentres.push_back(inst);
      }
    }
  }
  std::cout<< "completed all the passes. " << std::endl;
  Weights w(tempCentres.size());
  std::fill(w.begin(), w.end(), 1);
//  for (auto &inst:d) {
//    dist minDist = std::numeric_limits<dist>::max();
//    int temp = 0;
//    for (int i = 0; i < tempCentres.size(); ++i) {
//      if (KmeansHelpers::shortestDistanceToClusterCentre(tempCentres, inst) < minDist) {
//        temp = i;
//      }
//    }
//    ++w[temp];
//  }
//  for (auto &weight:w) {
//    if (weight == 0) weight = 1;
//  }
  KmeansBase *kmeans = new KmeansInstance<KmeansppSeedPicker, IR>();
  kmeans->cluster(tempCentres, centres, w, k);
  std::cout << "Finished picking seeds for KmeansII" << std::endl;
  return true;
};


#endif //KMEANSII_SEEDPICKERS_H
