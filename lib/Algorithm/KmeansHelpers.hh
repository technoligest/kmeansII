//
// Created by Yaser Alkayale on 2017-06-20.
//

#ifndef KMEANSII_KMEANSHELPERS_H
#define KMEANSII_KMEANSHELPERS_H


#include <cmath>
#include "../handlers/data.hh"

namespace KmeansHelpers {
//checks that all of the instances in the dataset are of teh same size
 inline bool analyzeDataset(const Dataset &d) {
   for (Instance i:d) {
     if (i.size() != d[0].size()) {
       return false;
     }
   }
   return true;
 }

//squared euclidean distance
 inline dist findDistanceSquared(const Instance &r1, const Instance &r2) {
   if (r1.size() != r2.size())
     return -1;
   dist result = 0;
   size_t size = r1.size();
   for (int i = 0; i < size; ++i) {
     result += pow(r1[i] - r2[i], 2);
   }
   return result;
 }

 //find the shortest distance to any already chosen cluster for the given row.
 inline dist shortestDistanceToClusterCentre(const std::vector<Instance> &centres, const Instance &inst) {
   if (centres.empty())
     return -1;

   dist currDistance, lowestDistance;
   lowestDistance = currDistance = findDistanceSquared(inst, centres[0]);

   for (Instance const &centre: centres) {
     currDistance = findDistanceSquared(inst, centre);
     if (currDistance < lowestDistance) {
       lowestDistance = currDistance;
     }
   }
   return lowestDistance;
 }

// inline const Instance *closestCentre(const std::vector<Instance> &centres, const Instance &inst){
//   if (centres.empty())
//     return nullptr;
//
//   const Instance *result = &(centres[0]);
//   dist currDistance, lowestDistance;
//   lowestDistance = currDistance = findDistanceSquared(inst, centres[0]);
//
//   for (Instance const &centre: centres) {
//     currDistance = findDistanceSquared(inst, centre);
//     if (currDistance < lowestDistance) {
//       result = &centre;
//       lowestDistance = currDistance;
//     }
//   }
//   return result;
// }


//DX is the sum of the shortest paths from each item to the nearest cluster.
 inline double calcDX(const Dataset &d, const std::vector<Instance> &centres) {
   if (centres.size() < 1) {
     return -1;
   }
   double result = 0;
   for (Instance const &inst: d) {
     result += shortestDistanceToClusterCentre(centres, inst);
//     std::cout<<"result: "<<result<<std::endl;
   }
   return result;
 }

 inline bool prepareForClustering(const Dataset &d, std::vector<Instance> &centres, const Weights &weights, ull k) {
   using namespace std;
   if (d.empty() || d.size() < k || k < 1) {
     std::cout << "Cannot cluster data with empty dataset or one with too few values of k values of less than 1."
               << endl;
     return false;
   }
   if (weights.size() != d.size()) {
     std::cout << "Number of weights does not match number of instances provided." << endl;
     return false;
   }

   //check that the dataset is all of the same size
   if (!analyzeDataset(d)) {
     std::cout << "cannot cluster data that is not consistent." << endl;
     return false;
   }

   int m = d[0].size(); //size of each instance in the dataset;s

   //resizing the centres vector to the right size.  i.e. the given number k
   centres.resize(k);

   //resizing all of the centres to the right size;
   for (Instance i:centres) {
     i.resize(m);
   }
   return true;
 }

}


#endif //KMEANSII_KMEANSHELPERS_H
