//
// Created by Yaser Alkayale on 2017-06-21.
//
#include "SeedPickers.hh"

using namespace KmeansHelpers;

bool RandomSeedPicker::pickSeeds(const Dataset &d, Dataset &centres, const Weights &weights, ull k) {
  std::cout<<"Started picking random seeds for Kmeans"<<std::endl;
  if (d.empty() || centres.empty() || d.size() < k) {
    return false;
  }
  centres.clear();
  size_t n = d.size();


  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(0, 1);

  for (int i = 0; i < k; ++i) {
    centres.push_back(d[static_cast<int>((dis(gen) * n))]);
  }
  std::cout<<"Finished picking random seeds for Kmeans"<<std::endl;
  return true;
};
bool KmeansppSeedPicker::pickSeeds(const Dataset &d, Dataset &centres, const Weights &weights, ull k) {
  std::cout<<"Started picking seeds for Kmeans++"<<std::endl;
  if (d.empty() || centres.empty() || d.size() < k) {
    return false;
  }

  centres.clear();
  size_t n = d.size();

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(0, 1);
  int count =0 ;
  centres.push_back(d[static_cast<int>((dis(gen) * n))]);
  for (int i = 1; i < k; ++i) {

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1);

    double dx = calcDX(d, centres);
    double ran = static_cast<double>(dis(gen));

    double cumulativeProb = 0;
    /*
     * The way the point is picked here is by picking a random number between 0 and 1.
     * Adding the probabilies of each of the points which we know equals to 1 will allow us
     * to choose the right point once the cumulative is more than the randomly chosen number.
     *
     * */
    for (int instId = 0; instId < d.size(); ++instId) {
      Instance inst = d[instId];
      double distance = shortestDistanceToClusterCentre(centres, inst) / dx * weights[instId];
      cumulativeProb += distance;
      if (ran <= cumulativeProb) {
        centres.push_back(inst);
        break;
      }
    }
  }
  assert(centres.size() == k);
  std::cout<<"Finished picking seeds for Kmeans++"<<std::endl;
  return true;
};




