//
// Created by Yaser Alkayale on 2017-05-29.
//

#ifndef KMEANSII_KMEANS_H
#define KMEANSII_KMEANS_H


#include "KmeansInitializer.hh"
#include "SeedPickers.hh"
#include "IterationRunners.hh"
#include "KmeansHelpers.hh"
#include "KmeansIIInitializer.hh"

//IR = iterationRunner

template<class IR = LiyoidsIteration>
using Kmeans = KmeansInitializer<RandomSeedPicker,IR>;

template <class IR = LiyoidsIteration>
using Kmeanspp = KmeansInitializer<KmeansppSeedPicker, IR>;

template<typename InnerIR = LiyoidsIteration, typename OuterIR = LiyoidsIteration>
using KmeansII = KmeansInitializer<KmeansIISeedPicker<InnerIR>,OuterIR>;



#endif //KMEANSII_KMEANS_H

