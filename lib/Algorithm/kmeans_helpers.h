//
// Created by Yaser Alkayale on 2017-06-20.
//

#ifndef KMEANSII_KMEANSHELPERS_H
#define KMEANSII_KMEANSHELPERS_H

#include "kmeans_data.h"


namespace kmeans{
namespace helpers{

inline bool equals(Instance &, Instance &);

//checks that all of the instances in the dataset_ are of teh same size
inline bool
analyzeDataset(const Dataset &);

/*
 * squared euclidean distance
 * Requires that the size of both instances is identical.
 */
Distance findDistanceSquared(const Instance &, const Instance &);

size_t findBelongingCentrePosition(const Instance &, const Dataset &);

//find the shortest distance to any already chosen cluster for the given row.
Distance shortestDistanceToClusterCentre(const Instance &, const Dataset &);

//DX is the sum of the shortest paths from each item to the nearest cluster. i.e. Objective function
Distance calcDX(const Dataset &dataset, const Weights& weights, const Dataset &centres);

bool prepareForClustering(const Dataset &, const Weights &, const ull &, Dataset &);

} //namespace kmeans
} //namespace helpers


#endif //KMEANSII_KMEANSHELPERS_H
