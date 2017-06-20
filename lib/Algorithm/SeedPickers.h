//
// Created by Yaser Alkayale on 2017-06-19.
//

#ifndef KMEANSII_SEEDPICKERS_H
#define KMEANSII_SEEDPICKERS_H

#include <random>
#include <cassert>
#include "../Algorithm/KmeansHelpers.h"


using namespace KmeansHelpers;


class SeedPicker {
public:
  virtual bool pickSeeds(const Dataset &d, Dataset &centres, const Weights &weights, ull k)=0;
};

class RandomSeedPicker : public SeedPicker {
public:
  inline RandomSeedPicker() {}

  inline bool pickSeeds(const Dataset &d, Dataset &centres, const Weights &weights, ull k) {
    if (d.empty() || centres.empty() || d.size() < k) {
      return false;
    }
    centres.clear();
    size_t n = d.size();


    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1);

    for (int i = 0; i < k; ++i) {
      centres.push_back(d[static_cast<int>((dis(gen) * n))]);
    }
    return true;
  }
};

class KmeansppSeedPicker : public SeedPicker {
public:
  inline KmeansppSeedPicker() {}

  inline bool pickSeeds(const Dataset &d, Dataset &centres, const Weights weights, ull k) {
    if (d.empty() || centres.empty() || d.size() < k) {
      return false;
    }

    centres.clear();
    size_t n = d.size();

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1);

    centres.push_back(d[static_cast<int>((dis(gen) * n))]);
    for (int i = 1; i < k; ++i) {

      std::random_device rd;
      std::mt19937 gen(rd());
      std::uniform_real_distribution<> dis(0, 1);

      double dx = calcDX(d, centres);
      double ran = static_cast<double>(dis(gen));

      double cumulativeProb = 0;
      /*
       * The way the point is picked here is by picking a random number between 0 and 1.
       * Adding the probabilies of each of the points which we know equals to 1 will allow us
       * to choose the right point once the cumulative is more than the randomly chosen number.
       *
       * */
      for (int instId = 0; instId < d.size(); ++instId) {
        Instance inst = d[instId];
        double distance = shortestDistanceToClusterCentre(centres, inst) / dx * weights[instId];
        cumulativeProb += distance;
        if (ran <= cumulativeProb) {
          centres.push_back(inst);
          break;
        }
      }
    }
    assert(centres.size() == k);
    return true;
  }
};

class KmeansIISeedPicker : public SeedPicker {
public:
  inline KmeansIISeedPicker(double _l) : l(_l) {}

  inline bool pickSeeds(const Dataset &d, Dataset &centres, const Weights weights, ull k) {
    if (d.empty() || centres.empty() || d.size() < k) {
      return false;
    }
    centres.clear();

    size_t n = d.size();

    //initializing random distribution
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1);

    centres.push_back(d[static_cast<int>((dis(gen) * n))]);
    double dx = calcDX(d, centres);
    ll passes = static_cast<int>( log(dx) / log(2));
    for (ll i = 0; i < passes; ++i) {
      double dx = calcDX(centres, centres);
      double ran = static_cast<double>(dis(gen));
      for (const Instance &inst: d) {
        double probability = l * shortestDistanceToClusterCentre(centres, inst) / dx;
        if (ran <= probability) {
          centres.push_back(inst);
        }
      }
    }
    return true;
  }

private:
  double l;
};


#endif //KMEANSII_SEEDPICKERS_H
