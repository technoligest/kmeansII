//
// Created by Yaser Alkayale on 2017-06-04.
//

#include <cassert>
#include <random>
#include "KmeansII.h"
#include "KmeansHelpers.h"

KmeansII::KmeansII(double osf) : l(osf) {} //osf=oversampling factor

KmeansII::~KmeansII() {}

using namespace std;

double KmeansII::cluster(Dataset &d, std::vector<Instance> &centres, Weights weights, ull k) {
  if (!KmeansHelpers::prepareForClustering(d, centres, weights, k)) {
    return -1;
  }
  std::vector<Instance> tempCentres;
  KmeansIISolver::findCentres(d, tempCentres, k, l);

  Kmeanspp sol;
  sol.cluster(tempCentres, centres, k);

  return KmeansSolver::runLiyodIterations(d, centres, weights);
}

double KmeansII::cluster(Dataset &d, std::vector<Instance> &centres, ull k) {


}

