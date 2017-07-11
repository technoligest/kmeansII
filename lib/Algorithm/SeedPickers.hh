//
// Created by Yaser Alkayale on 2017-06-19.
//

#ifndef KMEANSII_SEEDPICKERS_H
#define KMEANSII_SEEDPICKERS_H

#include <random>
#include <cassert>
#include <vector>
#include "data.hh"
#include "KmeansHelpers.hh"
#include "KmeansInstance.hh"
#include "SeedPickerBase.hh"

namespace kmeans{

class RandomSeedPicker : public SeedPicker{
public:
  inline RandomSeedPicker(){}

  bool pickSeeds(const Dataset &d, Dataset &centres, const Weights &weights, ull k) override;
};


class KmeansppSeedPicker : public SeedPicker{
public:
  inline KmeansppSeedPicker(){}

  bool pickSeeds(const Dataset &d, Dataset &centres, const Weights &weights, ull k) override;
};

template<class IR>
class KmeansIISeedPicker : public SeedPicker{
public:
  inline KmeansIISeedPicker(double _l, ull _r) : l(_l), r(_r){}

  bool pickSeeds(const Dataset &d, Dataset &centres, const Weights &weights, ull k) override;

private:
  double l;
  ull r;
};

//definition of this class is included here because it is mandatory since it is a templated class.
template<class IR>
bool KmeansIISeedPicker<IR>::pickSeeds(const Dataset &d, Dataset &centres, const Weights &weights, ull k){
  std::cout << "Started picking seeds for KmeansII" << std::endl;
  if(d.empty() || centres.empty() || d.size() < k){
    return false;
  }

  size_t n = d.size(); //number of point in the dataset

  //initializing random distribution
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(0, 1);


  std::vector<Instance> tempCentres;
  tempCentres.push_back(d[static_cast<int>((dis(gen) * n))]);
  double dx = helpers::calcDX(d, tempCentres, weights);

  ll passes = (r == -1) ? (static_cast<int>( log(dx) / log(2))) : r;
  std::cout << "numpasses: " << passes << std::endl;
  for(ll i = 0; i < passes; ++i){
    std::cout << "Starting pass: " << i << std::endl;
    dx = helpers::calcDX(d, tempCentres, weights);
    for(int instId = 0; instId < d.size(); ++instId){
      Instance inst = d[instId];
      double probability = l * helpers::shortestDistanceToClusterCentre(inst,tempCentres) / dx *
                           weights[instId];
      //std::cout<<weights[instId]<<std::endl;

      double ran = static_cast<double>(dis(gen));
      //std::cout << probability << "\t" << ran << std::endl;
      if(ran <= probability){
        //std::cout<<"added!"<<std::endl;
        tempCentres.push_back(inst);
      }
    }
    std::cout << "size of centres: " << tempCentres.size() << std::endl;
  }


  std::cout << "completed all the passes. " << std::endl;
  Weights w(tempCentres.size());
  std::fill(w.begin(), w.end(), 0);
  for(auto &inst:d){
    dist minDist = std::numeric_limits<dist>::max();
    int temp = 0;
    for(int tempCentreId = 0; tempCentreId < tempCentres.size(); ++tempCentreId){
      double dist = helpers::findDistanceSquared(tempCentres[tempCentreId], inst);
      if(dist < minDist){
        minDist = dist;
        temp = tempCentreId;
      }
    }
    w[temp] += 1;
  }
  for(const auto &i: w){
    std::cout << i << std::endl;
  }
  std::cout << "The seeds being sent into Kmeans++ from Kmeans||:" << std::endl;
  for(const auto &i:tempCentres){
    std::cout << i << std::endl;
  }
  std::cout << std::endl;
  KmeansBase *kmeans = new KmeansInstance<KmeansppSeedPicker, IR>();
  kmeans->cluster(tempCentres, centres, w, k);
  delete kmeans;

  std::cout << "The final seeds picked by kmeans+++ for Kmean||:";
  for(const auto &i:centres){
    std::cout << i << std::endl;
  }
  std::cout << "Finished picking seeds for KmeansII" << std::endl;
  return true;
};
} //namspace kmeans


#endif //KMEANSII_SEEDPICKERS_H
