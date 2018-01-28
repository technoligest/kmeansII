//
// Created by Yaser Alkayale on 2017-06-20.
//

#ifndef KMEANSII_KMEANSHELPERS_H
#define KMEANSII_KMEANSHELPERS_H

#include "kmeans_data.h"
#include "globals.h"


namespace kmeans{
namespace utils{

//checks that all of the instances in the dataset_ are of teh same size
bool analyzeDataset(const Dataset &);

/*
 * squared euclidean distance
 * Requires that the size of both instances is identical.
 */
Distance distanceSquared(const Instance &, const Instance &);

/*
 * Gives the centrePosition in the centres vector which is closest to the instance.
 */
size_t findBelongingCentrePosition(const Instance &, const Dataset &);

Distance distanceToClosestCentre(const Instance &, const Dataset &);

/*
 * Sum of distances to closest cluster centre.
 */
Distance dx(const Dataset &dataset, const Weights &weights, const Dataset &centres);


/*
 * Check that everything is good for clustering.
 */
bool prepareForClustering(const Dataset &, const Weights &, const ull &, Dataset &);

} //namespace kmeans
} //namespace utils


#endif //KMEANSII_KMEANSHELPERS_H
