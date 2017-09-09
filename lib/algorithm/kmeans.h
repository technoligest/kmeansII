/*
 *
 * Created by Yaser Alkayale on 2017-05-29.
 * This class gives us access to all the implementations of the kmenas algorithm.
 * Including this class in your runner, will allow you to use all the functions
 * and classes within the algorithm. No additional includes from the algorithm are required.
 *
 */

#ifndef KMEANSII_KMEANS_H
#define KMEANSII_KMEANS_H



#include "kmeans_instance.h"
#include "kmeans_ii_instance.h"
#include "seed_pickers.h"
#include "iteration_runners.h"
#include "kmeans_utils.h"
#include "kmeans_io.h"
#include "kmeans_input_arguments.h"

namespace kmeans{


template<class IterationRunner = LloydIterationRunner>
using Kmeans = KmeansInstance<RandomSeedPicker, IterationRunner>;

template<class IterationRunner = LloydIterationRunner>
using Kmeanspp = KmeansInstance<KmeansppSeedPicker, IterationRunner>;

template<typename InnerIR = LloydIterationRunner, typename OuterIR = LloydIterationRunner>
using KmeansII = KmeansInstance<KmeansIISeedPicker<InnerIR>, OuterIR>;

} //namespace kmeans

#endif //KMEANSII_KMEANS_H

