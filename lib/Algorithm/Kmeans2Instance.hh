//
// Created by Yaser Alkayale on 2017-06-27.
//

#ifndef KMEANSII_KMEANS2INSTANCE_HH
#define KMEANSII_KMEANS2INSTANCE_HH

#include "SeedPickers.hh"
#include "KmeansBase.hh"
#include "KmeansHelpers.hh"

namespace kmeans{
template<class InnerIR, class OuterIR>
class KmeansInstance<KmeansIISeedPicker<InnerIR>, OuterIR> : public KmeansBase{
public:
  inline KmeansInstance(double _l, ull _r){
    sp = new KmeansIISeedPicker<InnerIR>(_l, _r);
    ir = new OuterIR();
  };
};
} //namespace kmeans
#endif //KMEANSII_KMEANS2INSTANCE_HH
