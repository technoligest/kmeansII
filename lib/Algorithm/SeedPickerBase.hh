//
// Created by Yaser Alkayale on 2017-07-11.
//

#ifndef KMEANSII_SEEDPICKERBASE_HH
#define KMEANSII_SEEDPICKERBASE_HH


#include "data.hh"

namespace kmeans{
class SeedPicker{
public:
  virtual bool
  pickSeeds(const Dataset &d, Dataset &centres, const Weights &weights, ull k)=0;
};
}//namespace kmeans



#endif //KMEANSII_SEEDPICKERBASE_HH
