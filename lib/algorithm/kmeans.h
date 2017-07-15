//
// Created by Yaser Alkayale on 2017-05-29.
//

#ifndef KMEANSII_KMEANS_H
#define KMEANSII_KMEANS_H

#include "kmeans_base.h"
#include "kmeans_instance.h"
#include "kmeans_ii_instance.h"
#include "seed_pickers.h"
#include "iteration_runners.h"
#include "kmeans_helpers.h"

namespace kmeans{

//IR = iterationRunner

template<class IterationRunner = LloydIterationRunner>
using Kmeans = KmeansInstance<RandomSeedPicker, IterationRunner>;

template<class IterationRunner = LloydIterationRunner>
using Kmeanspp = KmeansInstance<KmeansppSeedPicker, IterationRunner>;

template<typename InnerIR = LloydIterationRunner, typename OuterIR = LloydIterationRunner>
using KmeansII = KmeansInstance<KmeansIISeedPicker<InnerIR>, OuterIR>;

} //namespace kmeans

#endif //KMEANSII_KMEANS_H

