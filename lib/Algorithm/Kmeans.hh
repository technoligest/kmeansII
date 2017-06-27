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

//IR = iterationRunner

template<class IR = LloydsIteration>
using Kmeans = KmeansInstance<RandomSeedPicker,IR>;

template <class IR = LloydsIteration>
using Kmeanspp = KmeansInstance<KmeansppSeedPicker, IR>;

template<typename InnerIR = LloydsIteration, typename OuterIR = LloydsIteration>
using KmeansII = KmeansInstance<KmeansIISeedPicker<InnerIR>,OuterIR>;


#endif //KMEANSII_KMEANS_H

