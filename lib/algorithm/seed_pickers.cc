//
// Created by Yaser Alkayale on 2017-06-21.
//
#include "seed_pickers.h"
#include "kmeans_utils.h"
#include "iteration_runners.h"
#include "kmeans.h"

namespace kmeans{
const std::string NewSeedPicker::name_ = "Yaser's Seed Picker";
const std::string KmeansppSeedPicker::name_ = "Kmeans++ Seed Picker";
const std::string RandomSeedPicker::name_ = "Random Seed Picker";


bool NewSeedPicker::pickSeeds(const Dataset &d, const Weights &weights, ull k, Dataset &centres) {


  LloydIterationRunner iterationRunner(iterations_);

  Kmeans <>instance(&iterationRunner);
  Dataset runsCentres;
  Dataset tempCentres;
  for(ull i = 0; i < runs_; ++i) {
    tempCentres.clear();
    instance.cluster(d, weights, k, tempCentres);
    runsCentres.insert(runsCentres.end(), tempCentres.begin(), tempCentres.end());
  }
  Kmeans<> instance2;
  instance2.cluster(runsCentres, Weights(runsCentres.size(), 1), k, centres);
  return true;
}


bool RandomSeedPicker::pickSeeds(const Dataset &dataset, const Weights &weights, ull k, Dataset &centres) {

  if(dataset.empty() || k < 1 || dataset.size() < k) {
    return false;
  }
  centres.clear();
  size_t n = dataset.size();


  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(0, 1);

  for(int i = 0; i < k; ++i) {
    centres.push_back(dataset[static_cast<int>((dis(gen) * n))]);
  }
  return true;
};


bool KmeansppSeedPicker::pickSeeds(const Dataset &d, const Weights &weights, ull k, Dataset &centres) {

  if(d.empty() || centres.empty() || d.size() < k) {
    return false;
  }

  centres.clear();
  size_t n = d.size();

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(0, 1);

  centres.push_back(d[static_cast<int>((dis(gen) * n))]);
  for(int i = 1; i < k; ++i) {

    double dx = utils::dx(d, weights, centres);
    double ran = static_cast<double>(dis(gen));

    /*
     * The way the point is picked here is by picking a random number between 0 and 1.
     * Adding the probabilies of each of the points which we know equals to 1 will allow us
     * to choose the right point once the cumulative is more than the randomly chosen number.
     *
     * */
    double cumulativeProb = 0;
    for(int instId = 0; instId < d.size(); ++instId) {
      Instance inst = d[instId];
      double distance = utils::distanceToClosestCentre(inst, centres) / dx * weights[instId];
      cumulativeProb += distance;
      if(ran <= cumulativeProb) {
        centres.push_back(inst);
        break;
      }
    }
  }
  assert(centres.size() == k);
  return true;
};
} //namspace kmeans



