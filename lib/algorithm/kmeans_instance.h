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
    seed_picker_ = new SP();
    iteration_runner_ = new IR();
  };
};
} //namespace kmeans

#endif //KMEANSII_KMEANSIIINITIALIZER_HH




