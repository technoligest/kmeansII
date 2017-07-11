/*
 * Created by Yaser Alkayale on 2017-06-22.
 *
 *
 *
 */

#ifndef KMEANSII_KMEANSINSTANCE_HH
#define KMEANSII_KMEANSINSTANCE_HH

#include <iostream>
#include "KmeansBase.hh"
#include "KmeansHelpers.hh"
#include "data.hh"

namespace kmeans{
template<class SP, class IR>
class KmeansInstance : public KmeansBase{
public:
  inline KmeansInstance(){
    sp = new SP();
    ir = new IR();
  };
};
} //namespace kmeans

#endif //KMEANSII_KMEANSIIINITIALIZER_HH




