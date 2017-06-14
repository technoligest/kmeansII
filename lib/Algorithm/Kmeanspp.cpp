//
// Created by Yaser Alkayale on 2017-06-01.
//

#include "Kmeanspp.h"
#include <cassert>
#include <random>

Kmeanspp::Kmeanspp() {}

Kmeanspp::~Kmeanspp() {};

using namespace KmeansSolver;
using namespace std;
namespace KmeansppSolver {
 //find the shortest distance to any already chosen cluster for the given row.
 double shortestDistanceToClusterCentre(const std::vector<Instance> &centres, const Instance &inst) {
   if (centres.empty())
     return -1;

   double currDistance, lowestDistance;
   lowestDistance = currDistance = KmeansSolver::findDistanceSquared(inst, centres[0]);

   for (Instance const &centre: centres) {
     currDistance = findDistanceSquared(inst, centre);
     if (currDistance < lowestDistance) {
       lowestDistance = currDistance;
     }
   }
   return lowestDistance;
 }

//DX is the sum of the shortest paths from each item to the nearest cluster.
 double calcDX(const Dataset &d, const std::vector<Instance> &centres) {
   if (centres.size() < 1) {
     return -1;
   }
   double result = 0;
   for (Instance const &inst: d) {
     result += shortestDistanceToClusterCentre(centres, inst);
   }
   return result;
 }

 void findCentres(Dataset &d, std::vector<Instance> &centres, ull k) {
   assert(k > 0);
   assert(d.size() > k);
   centres.clear();

   size_t n = d.size();

   std::random_device rd;
   std::mt19937 gen(rd());
   std::uniform_real_distribution<> dis(0, 1);

   centres.push_back(d[static_cast<int>((dis(gen) * n))]);
   for (int i = 1; i < k; ++i) {

     std::random_device rd;
     std::mt19937 gen(rd());
     std::uniform_real_distribution<> dis(0, 1);

     double dx = calcDX(d, centres);
     double ran = static_cast<double>(dis(gen));

     double cumulativeProb = 0;
     for (Instance inst:d) {
       double distance = shortestDistanceToClusterCentre(centres, inst) / dx;
       cumulativeProb += distance;
       if (ran <= cumulativeProb) {
         centres.push_back(inst);
         break;
       }
     }

   }
   assert(centres.size()==k);
 }
}


double Kmeanspp::cluster(Dataset &d, std::vector<Instance> &centres, ull k) {
  if(!KmeansSolver::prepareForClustering(d,centres,k)){
    return -1;
  }
  KmeansppSolver::findCentres(d, centres, k);
  return KmeansSolver::runLiyodIterations(d, centres);
}

