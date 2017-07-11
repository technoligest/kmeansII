//
// Created by Yaser Alkayale on 2017-06-20.
//

#ifndef KMEANSII_KMEANSHELPERS_H
#define KMEANSII_KMEANSHELPERS_H


#include <cmath>
#include "data.hh"
#include <cassert>

namespace kmeans{
namespace helpers{

inline bool equals(Instance &l, Instance &r){
  if(l.size() != r.size())
    return false;
  for(size_t i = 0; i < l.size(); ++i){
    if(l[i] != r[i])
      return false;
  }
  return true;
}

//checks that all of the instances in the dataset are of teh same size
inline bool
analyzeDataset(const Dataset &d){
  for(Instance i:d){
    if(i.size() != d[0].size()){
      return false;
    }
  }
  return true;
}

/*
 * squared euclidean distance
 * Requires that the size of both instances is identical.
 */
inline dist
findDistanceSquared(const Instance &r1, const Instance &r2){
  if(r1.size() != r2.size())
    return -1;
  dist result = 0;
  size_t size = r1.size();
  for(int i = 0; i < size; ++i){
    result += pow(r1[i] - r2[i], 2);
  }
  return result;
}


inline size_t
findBelongingCentrePosition(const Instance &inst, const Dataset &centres){
  assert(!centres.empty() && !inst.empty());
  size_t minDistClusterId = 0;
  double minDist = findDistanceSquared(inst, centres[0]);
  for(int i = 1; i < centres.size(); ++i){
    const Instance &centre = centres[i];
    double newDist = findDistanceSquared(inst, centre);
    if(newDist < minDist){
      minDist = newDist;
      minDistClusterId = i;
    }
  }
  return minDistClusterId;
}

//find the shortest distance to any already chosen cluster for the given row.
inline dist
shortestDistanceToClusterCentre(const Instance &inst, const Dataset &centres){
  assert(!centres.empty() && !inst.empty());
  return findDistanceSquared(centres[findBelongingCentrePosition(inst, centres)], inst);
}

//DX is the sum of the shortest paths from each item to the nearest cluster.
inline double
calcDX(const Dataset &d, const Dataset &centres,
       const Weights weights){
  if(centres.size() < 1 || d.size() != weights.size()){
    return -1;
  }
  double result = 0;
  for(int i = 0; i < d.size(); ++i){
    result += shortestDistanceToClusterCentre(d[i], centres) * weights[i];
  }
  return result;
}

inline bool
prepareForClustering(const Dataset &d, Dataset &centres,
                     const Weights &weights, ull k){
  if(d.empty() || d.size() < k || k < 1){
    std::cout << "Cannot cluster data with empty dataset or one with too few values of k values of less than 1."
              << std::endl;
    return false;
  }
  if(weights.size() != d.size()){
    std::cout << "Number of weights does not match number of instances provided." << std::endl;
    return false;
  }

  //check that the dataset is all of the same size
  if(!analyzeDataset(d)){
    std::cout << "cannot cluster data that is not consistent." << std::endl;
    return false;
  }

  int m = d[0].size(); //size of each instance in the dataset;s

  //resizing the centres vector to the right size.  i.e. the given number k
  centres.resize(k);

  //resizing all of the centres to the right size;
  for(Instance i:centres){
    i.resize(m);
  }
  return true;
}
} //namespace kmeans
} //namespace helpers


#endif //KMEANSII_KMEANSHELPERS_H
