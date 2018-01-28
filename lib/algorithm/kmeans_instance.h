/*
 * Created by Yaser Alkayale on 2017-06-22.
 *
 *
 */

#ifndef KMEANSII_KMEANSINSTANCE_HH
#define KMEANSII_KMEANSINSTANCE_HH

#include <iostream>
#include "kmeans_base.h"

namespace kmeans{
template<class SP, class IR>
class KmeansInstance : public KmeansBase{
public:
  //TODO: Remove the pointer implementation for a reference one
  inline explicit KmeansInstance(IterationRunner *iterationRunner = new IR(), SeedPicker *seedPicker= new SP()):
      KmeansBase(iterationRunner,seedPicker){};

  inline ~KmeansInstance() {}
};
} //namespace kmeans

#endif //KMEANSII_KMEANSIIINITIALIZER_HH




