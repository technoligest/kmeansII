/*
 * Created by Yaser Alkayale on 2017-06-22.
 *
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
  inline KmeansInstance(){
    seedPicker = new SP();
    iterationRunner = new IR();
  };

  inline ~KmeansInstance() {
    delete seedPicker;
    delete iterationRunner;
  }
};
} //namespace kmeans

#endif //KMEANSII_KMEANSIIINITIALIZER_HH




