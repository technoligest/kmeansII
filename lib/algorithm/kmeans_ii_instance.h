//
// Created by Yaser Alkayale on 2017-06-27.
//

#ifndef KMEANSII_KMEANS2INSTANCE_HH
#define KMEANSII_KMEANS2INSTANCE_HH

#include "seed_pickers.h"
#include "kmeans_base.h"

namespace kmeans{
template<class InnerIR, class OuterIR>
class KmeansInstance<KmeansIISeedPicker<InnerIR>, OuterIR> : public KmeansBase{
public:
  inline KmeansInstance(double _l, ull _r){
    seed_picker_ = new KmeansIISeedPicker<InnerIR>(_l, _r);
    iteration_runner_ = new OuterIR();
  };
};
} //namespace kmeans
#endif //KMEANSII_KMEANS2INSTANCE_HH
