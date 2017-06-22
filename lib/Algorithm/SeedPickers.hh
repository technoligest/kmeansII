//
// Created by Yaser Alkayale on 2017-06-19.
//

#ifndef KMEANSII_SEEDPICKERS_H
#define KMEANSII_SEEDPICKERS_H

#include <random>
#include <cassert>
#include "../handlers/data.hh"
#include "KmeansHelpers.hh"
#include "Kmeans.hh"


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
  inline KmeansIISeedPicker() : l(2) {}

  bool pickSeeds(const Dataset &d, Dataset &centres, const Weights &weights, ull k) override;

private:
  double l;
};

template<class IR>
bool KmeansIISeedPicker<IR>::pickSeeds(const Dataset &d, Dataset &centres, const Weights &weights, ull k) {
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
    double dx = KmeansHelpers::calcDX(tempCentres, tempCentres);
    double ran = static_cast<double>(dis(gen));
    for (const Instance &inst: d) {
      double probability = l * KmeansHelpers::shortestDistanceToClusterCentre(tempCentres, inst) / dx;
      if (ran <= probability) {
        tempCentres.push_back(inst);
      }
    }
  }
  KmeansBase *kmeans = new Kmeanspp<IR>();
  kmeans->cluster(tempCentres, centres, k);
  return true;
};


#endif //KMEANSII_SEEDPICKERS_H
