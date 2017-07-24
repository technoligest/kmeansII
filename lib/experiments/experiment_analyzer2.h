//
// Created by Yaser Alkayale on 2017-07-16.
//

#ifndef KMEANSII_EXPERIMENT_ANALYZER2_H
#define KMEANSII_EXPERIMENT_ANALYZER2_H

#include <unordered_map>
#include <cassert>
#include "../algorithm/kmeans_data.h"
#include "experiment_result.h"
#include "../algorithm/kmeans_helpers.h"
#include "perfect_matching_uncompleted_deprecated.h"
#include "centre_intersections.h"

namespace kmeans{
namespace experiments{

class ExperimentAnalyzer2{
private:
  const Dataset &dataset_; //TODO Why do we need this?
  std::unordered_map<ull, Instance> idToInstanceMap_; //TODO why do we need this?

  std::vector<ExperimentResult> experimentResults_; //TODO find a better name than experimentResult, will also have to be changed in the class definition too
  Matrix<int> pointPositions_; //TODO Find a better name for this the matrix that norbert came up with.
  std::vector<CentreIntersections> intersections;


  inline void populatePointMaps() {
    for(size_t i = 0; i < dataset_.size(); ++i) {
      idToInstanceMap_.insert({i, dataset_[i]});
    }
  }

  /*
   * calculate the matrix for distances between every instance and every other instance in datasets
   * the two datasets must be of equal size.
   * If 2 instances are the same, then the distance between them is set to numeric_limit of distance
   */
  inline Matrix<Distance> calDistanceMatrix(const Dataset &dataset1, const Dataset &dataset2) {
    Matrix<Distance> result{dataset1.size(), std::vector<Distance>(dataset2.size(), 0)};
    for(size_t dataset1InstanceId = 0; dataset1InstanceId < dataset1.size(); ++dataset1InstanceId) {
      for(size_t dataset2InstanceId = dataset1InstanceId; dataset2InstanceId < dataset2.size(); ++dataset2InstanceId) {
        Distance tempDistance = helpers::findDistanceSquared(dataset1[dataset1InstanceId],
                                                             dataset2[dataset2InstanceId]);
        //tempDistance = (tempDistance == 0) ? std::numeric_limits<Distance>::max() : tempDistance;
        result[dataset1InstanceId][dataset2InstanceId] = tempDistance;
        if(dataset1InstanceId < dataset2.size() && dataset2InstanceId < dataset1.size()) {
          result[dataset2InstanceId][dataset1InstanceId] = tempDistance;
        }
      }
    }
  }

  inline void reorderExperimentCentres() {
    if(experimentResults_.size() < 2) return;
    auto baseCentres = experimentResults_[0].centres;
    for(size_t experimentResultId = 0;
        experimentResultId < experimentResults_[0].centres.size(); ++experimentResultId) {
      auto distanceMatrix = calDistanceMatrix(baseCentres, experimentResults_[experimentResultId].centres);
      PerfectMatching perfectMatchig(distanceMatrix);
      auto matchingCentres = perfectMatchig.runAlgorithm();
      for(size_t i = 0; i < matchingCentres.size(); ++i) {
        if(i == matchingCentres[i]) continue;
        std::swap(experimentResults_[experimentResultId].centres[i],
                  experimentResults_[experimentResultId].centres[matchingCentres[i]]);
        std::cout << "Swapped!" << std::endl;
      }
    }
  }

  void calculatePointPositions() {
    for(size_t experimentId = 0; experimentId < experimentResults_.size(); ++experimentId) {
      for(size_t instanceId = 0; instanceId < dataset_.size(); ++instanceId) {
        pointPositions_[experimentId][instanceId] = helpers::findBelongingCentrePosition(dataset_[instanceId],
                                                                                         experimentResults_[experimentId].centres);
      }
    }
  }

  void calculateIntersection(const size_t &experiment1id, const size_t &experiment2id) {
    assert(experiment1id < pointPositions_.size());
    assert(experiment2id < pointPositions_.size());
    assert(experiment1id == experiment2id + 1);
    assert(experiment1id % 2 == 1);
    for(size_t instanceId = 0; instanceId < dataset_.size(); ++instanceId) {
      auto k = pointPositions_[experiment1id][instanceId];
      if(k == pointPositions_[experiment2id][instanceId]) {
        ++intersections[experiment2id / 2].instances[k].numCluster1;
        ++intersections[experiment2id / 2].instances[k].numCluster2;
        ++intersections[experiment2id / 2].instances[k].numIntersection;
      } else {
        ++intersections[experiment2id / 2].instances[k].numCluster1;
        auto k = pointPositions_[experiment2id][instanceId];
        ++intersections[experiment2id / 2].instances[k].numCluster2;
      }
    }
  }

  void calculateIntersections() {
    assert(experimentResults_.size() > 1);
    assert(experimentResults_.size() % 2 == 0);
    size_t k = experimentResults_[0].centres.size();
    for(size_t i = 0; i < k / 2; ++i) {
      intersections.push_back(
          CentreIntersections(std::vector<CentreIntersectionInstance>(k, CentreIntersectionInstance())));
    }
    for(size_t i = 0; i < experimentResults_.size(); i += 2) {
      calculateIntersection(i, i + 1);
    }
  }

public:
  ExperimentAnalyzer2(const std::vector<ExperimentResult> &er, const Dataset &dataset) : experimentResults_(er),
                                                                                         dataset_(dataset),
                                                                                         pointPositions_(
                                                                                             Matrix<int>(er.size(),
                                                                                                         std::vector<int>(
                                                                                                             dataset.size(),
                                                                                                             0))) {

    assert(dataset_.size() > 0);
    assert(experimentResults_.size() > 1);
    if(experimentResults_.size() % 2 == 1) {
      experimentResults_.resize(experimentResults_.size() - 1);
    }
    size_t k = experimentResults_[0].centres.size();
    assert(dataset_.size() > k);
    for(const auto &er:experimentResults_) {
      assert(er.centres.size() == k);
    }

    populatePointMaps();
    reorderExperimentCentres();
    calculatePointPositions();
    calculateIntersections();
  }


};
}//namespace experiments
}//namespae kmeans

#endif //KMEANSII_EXPERIMENT_ANALYZER2_H
