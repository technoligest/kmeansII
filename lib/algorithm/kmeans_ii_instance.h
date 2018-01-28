//
// Created by Yaser Alkayale on 2017-06-27.
//

#ifndef KMEANSII_KMEANS2INSTANCE_HH
#define KMEANSII_KMEANS2INSTANCE_HH

#include "seed_pickers.h"
#include "kmeans_base.h"

namespace kmeans{
/*
 * This class was needed because we need 2 extra parameters to instanciate a kmeansII
 * instance.
 */
template<class InnerIR, class OuterIR>
class KmeansInstance<KmeansIISeedPicker<InnerIR>, OuterIR> : public KmeansBase{
public:
  inline explicit KmeansInstance(double _l, ull _r){
    seedPicker_ = new KmeansIISeedPicker<InnerIR>(_l, _r);
    iterationRunner_ = new OuterIR();
  };
  inline ~KmeansInstance() {
    delete seedPicker_;
    delete iterationRunner_;
  }
};
} //namespace kmeans
#endif //KMEANSII_KMEANS2INSTANCE_HH
