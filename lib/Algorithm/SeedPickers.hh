//
// Created by Yaser Alkayale on 2017-06-19.
//

#ifndef KMEANSII_SEEDPICKERS_H
#define KMEANSII_SEEDPICKERS_H

#include <random>
#include <cassert>
#include "KmeansHelpers.hh"
#include "IterationRunners.hh"
#include "../handlers/data.hh"


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




template <class IR>
class KmeansIISeedPicker : public SeedPicker {
public:
  inline KmeansIISeedPicker() : l(2) {}

  bool pickSeeds(const Dataset &d, Dataset &centres, const Weights &weights, ull k) override;

private:
  double l;
};




#endif //KMEANSII_SEEDPICKERS_H
