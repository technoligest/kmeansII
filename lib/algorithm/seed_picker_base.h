//
// Created by Yaser Alkayale on 2017-07-11.
//

#ifndef KMEANSII_SEEDPICKERBASE_HH
#define KMEANSII_SEEDPICKERBASE_HH


#include "kmeans_data.h"

namespace kmeans{
class SeedPicker{
public:
  virtual bool pickSeeds(const Dataset &d, const Weights &weights, ull k, Dataset &centres)=0;
  virtual inline ~SeedPicker(){}
  virtual std::string name() = 0;

};
}//namespace kmeans



#endif //KMEANSII_SEEDPICKERBASE_HH
