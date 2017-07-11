//
// Created by Yaser Alkayale on 2017-05-29.
//

#ifndef KMEANSII_KMEANS_H
#define KMEANSII_KMEANS_H

#include "KmeansBase.hh"
#include "KmeansInstance.hh"
#include "Kmeans2Instance.hh"
#include "SeedPickers.hh"
#include "IterationRunners.hh"
#include "KmeansHelpers.hh"

namespace kmeans{

//IR = iterationRunner

template<class IR = LloydIterationRunner>
using Kmeans = KmeansInstance<RandomSeedPicker, IR>;

template<class IR = LloydIterationRunner>
using Kmeanspp = KmeansInstance<KmeansppSeedPicker, IR>;

template<typename InnerIR = LloydIterationRunner, typename OuterIR = LloydIterationRunner>
using KmeansII = KmeansInstance<KmeansIISeedPicker<InnerIR>, OuterIR>;

} //namespace kmeans

#endif //KMEANSII_KMEANS_H

