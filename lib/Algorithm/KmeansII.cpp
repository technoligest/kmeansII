//
// Created by Yaser Alkayale on 2017-06-04.
//

#include <cassert>
#include <random>
#include <cmath>
#include "KmeansII.h"

KmeansII::KmeansII(double osf):l(osf) {} //osf=oversampling factor

KmeansII::~KmeansII() {}

using namespace std;

namespace KmeansIISolver {
 void findCentres(Dataset &d, std::vector<Instance> &centres, ull k,ll l) {
   assert(k > 0);
   assert(d.size() > k);
   centres.clear();

   size_t n = d.size();

   //initializing random distribution
   std::random_device rd;
   std::mt19937 gen(rd());
   std::uniform_real_distribution<> dis(0, 1);

   centres.push_back(d[static_cast<int>((dis(gen) * n))]);
   double dx = KmeansppSolver::calcDX(d, centres);
   ll passes = static_cast<int>( log(dx)/log(2));
   cout<<"Number of passes: "<<passes<<endl;
   for (ll i = 0; i < passes; ++i) {
     double dx = KmeansppSolver::calcDX(centres, centres);
     double ran = static_cast<double>(dis(gen));
     for (Instance &inst: d) {
       double probability = l * KmeansppSolver::shortestDistanceToClusterCentre(centres, inst) / dx;
       if (ran <= probability) {
         centres.push_back(inst);
       }
     }
   }
 }
}

double KmeansII::cluster(Dataset &d, std::vector<Instance> &centres, ull k) {

  if (!KmeansSolver::prepareForClustering(d, centres, k)) {
    return -1;
  }
  std::vector<Instance> tempCentres;
  KmeansIISolver::findCentres(d, tempCentres, k, l);

  Kmeanspp sol;
  sol.cluster(tempCentres, centres, k);

  return KmeansSolver::runLiyodIterations(d, centres);
}

