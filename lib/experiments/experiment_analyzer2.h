//
// Created by Yaser Alkayale on 2017-07-16.
//

#ifndef KMEANSII_EXPERIMENT_ANALYZER2_H
#define KMEANSII_EXPERIMENT_ANALYZER2_H

#include <iostream>
#include <unordered_map>
#include <cassert>
#include "../algorithm/kmeans_data.h"
#include "../algorithm/kmeans_helpers.h"
#include "experiment_result.h"
#include "centre_intersections.h"
#include "experiments_bipartite_perfect_matching.h"
#include "experiment_helpers.h"

namespace kmeans{
namespace experiments{

class ExperimentAnalyzer2{
private:
  Dataset dataset_; //TODO Why do we need this?

  std::vector<ExperimentResult> experimentResults_; //TODO find a better name than experimentResult, will also have to be changed in the class definition too

  //pointPositions[m][n] is the cluster number of the m'th experiment with the n'th item instance in the dataset
  Matrix<int> pointPositions_; //TODO Find a better name for this the matrix that norbert came up with.

  /*
   * intersections[a][b][c]
   * for c=0: This is the number of points for cluster #b i in experiment (a*2)
   * for c=1: This is the number of points intersecting in experiments (a*2) and (a*2+1) for cluster #b
   * for c=2: This is the number of points for cluster #b i in experiment (a*2+1)
   *
   */
  std::vector<std::vector<std::vector<std::size_t>>> intersections;


  /*
   * calculate the matrix for distances between every instance and every other instance in datasets
   */
  inline Matrix<Distance> calcDistanceMatrix(const Dataset &dataset1, const Dataset &dataset2) {
    Matrix<Distance> result{dataset1.size(), std::vector<Distance>(dataset2.size(), 0)};
    for(size_t dataset1InstanceId = 0; dataset1InstanceId < dataset1.size(); ++dataset1InstanceId) {
      for(size_t dataset2InstanceId = 0; dataset2InstanceId < dataset2.size(); ++dataset2InstanceId) {
        result[dataset1InstanceId][dataset2InstanceId] = ::kmeans::helpers::findDistanceSquared(
            dataset1[dataset1InstanceId],
            dataset2[dataset2InstanceId]);
      }
    }
    return result;
  }

  /*
   * This reorders the centres in all of the experiments except for the first one.
   * It rearranges the centres so that the first centre in each of the experiments is approximately the same
   * over multiple runs.
   */
  inline void reorderExperimentCentres() {
    if(experimentResults_.size() < 2) return;
    auto baseCentres = experimentResults_[0].centres;
    for(size_t experimentId = 1; experimentId < experimentResults_[0].centres.size(); ++experimentId) {
      auto distanceMatrix = calcDistanceMatrix(baseCentres, experimentResults_[experimentId].centres);
      auto matchingPairs = minimumWeightPerfectMatching(distanceMatrix);
      Dataset tempCentres(baseCentres.size());
      for(const auto &pair:matchingPairs) {
        tempCentres[std::get<0>(pair)] = experimentResults_[experimentId].centres[std::get<1>(pair)];
      }

      for(std::size_t i=0; i<tempCentres.size(); ++i){
        std::cout<<tempCentres[i][0]<<" "<< baseCentres[i][0];
        std::cout<<",";
        std::cout<<tempCentres[i][1]<<" "<< baseCentres[i][1];
        std::cout<<std::endl;
      }
      std::cout<<"\n\n\n";
      experimentResults_[experimentId].centres = std::move(tempCentres);
    }
    std::cout << "finished all reorderings. " << std::endl;
  }

  void calculatePointPositions() {
    std::cout << "before reorderings. " << std::endl;
    reorderExperimentCentres();
    std::cout << "finished reordering experiments." << std::endl;

    for(size_t experimentId = 0; experimentId < experimentResults_.size(); ++experimentId) {
      for(size_t instanceId = 0; instanceId < dataset_.size(); ++instanceId) {
        assert(experimentId < pointPositions_.size());
        assert(instanceId < pointPositions_[experimentId].size());
        pointPositions_[experimentId][instanceId] = ::kmeans::helpers::findBelongingCentrePosition(dataset_[instanceId],
                                                                                                   experimentResults_[experimentId].centres);
      }
      std::cout << "finished points for experiment " << experimentId << std::endl;
    }
  }

  void calculateIntersection(const size_t &experiment1id) {
    assert(experiment1id < pointPositions_.size() - 1);
    assert(experiment1id % 2 == 0);
    const size_t &experiment2id = experiment1id + 1;
    for(size_t instanceId = 0; instanceId < dataset_.size(); ++instanceId) {
      auto k1 = pointPositions_[experiment1id][instanceId];
      auto k2 = pointPositions_[experiment2id][instanceId];
      if(k1 == k2) {
        ++intersections[experiment2id / 2][k1][0];
        ++intersections[experiment2id / 2][k1][1];
        ++intersections[experiment2id / 2][k1][2];
      } else {
        ++intersections[experiment2id / 2][k1][0];
        ++intersections[experiment2id / 2][k2][2];
      }
    }
    for(auto k:intersections[experiment2id / 2]) {
      std::cout << k[0] << ", " << k[1] << ", " << k[2] << std::endl;
    }
  }

  void calculateIntersections() {
    assert(experimentResults_.size() > 1);
    assert(experimentResults_.size() % 2 == 0);
    calculatePointPositions();
    std::cout << "calculating point positions is done" << std::endl;
    for(size_t i = 0; i < experimentResults_.size(); i += 2) {
      calculateIntersection(i);
    }
  }

  void validateDataset() {
    assert(dataset_.size() > 0);
    size_t k = experimentResults_[0].centres.size();
    assert(dataset_.size() > k);
    for(const auto &er:experimentResults_) {
      assert(er.centres.size() == k);
    }
  }

  void validateExperiments() {
    assert(experimentResults_.size() > 1);
    if(experimentResults_.size() % 2 == 1) {
      experimentResults_.resize(experimentResults_.size() - 1);
    }
  }

public:
  std::vector<double> calculateAverageIntersectionsOverUnion() {
    std::vector<double> result;
    for(const auto experimentIntersections: intersections) {
      double intersectionSum = 0;
      double unionSum = 0;
      for(const auto cluster: experimentIntersections) {
        intersectionSum += cluster[1];

        unionSum += cluster[0] + cluster[2] - cluster[1];
        std::cout << cluster[0] << ", " << cluster[1] << ", " << cluster[2] << std::endl;
      }
      //std::cout <<"intersection"<< intersectionSum << "union: "<<cluster[0] + cluster[2] - cluster[1]<<std::endl;
      result.push_back(intersectionSum / unionSum);
    }
    return result;
  }

  ExperimentAnalyzer2(const std::vector<ExperimentResult> &er, Dataset dataset) :
      experimentResults_(er),
      dataset_(dataset),
      pointPositions_(Matrix<int>(er.size(), std::vector<int>(dataset.size(), 0))) {

    validateExperiments();
    validateDataset();
    intersections = std::vector<std::vector<std::vector<std::size_t>>>(er.size() / 2,
                                                                       std::vector<std::vector<std::size_t>>(
                                                                           er[0].centres.size(),
                                                                           std::vector<std::size_t>(3, 0)));

    calculateIntersections();

    std::vector<double> intersectionsOverUnion = calculateAverageIntersectionsOverUnion();
    //std::cout << "caculating intersection over union is done.\n";
    //for(auto i:intersectionsOverUnion) {
    //  std::cout << i << std::endl;
    //}
    //using ::kmeans::operator<<;
    //for(auto r:pointPositions_) {
    //  for(auto k: r) {
    //    std::cout << k << " ";
    //  }
    //  std::cout << std::endl;
    //}

  }


};
}//namespace experiments
}//namespae kmeans

#endif //KMEANSII_EXPERIMENT_ANALYZER2_H
