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

template<class IR = LloydIterationRunner>
using Kmeans = KmeansInstance<RandomSeedPicker, IR>;

template<class IR = LloydIterationRunner>
using Kmeanspp = KmeansInstance<KmeansppSeedPicker, IR>;

template<typename InnerIR = LloydIterationRunner, typename OuterIR = LloydIterationRunner>
using KmeansII = KmeansInstance<KmeansIISeedPicker<InnerIR>, OuterIR>;

} //namespace kmeans

#endif //KMEANSII_KMEANS_H

