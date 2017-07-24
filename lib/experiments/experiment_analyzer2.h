//
// Created by Yaser Alkayale on 2017-07-16.
//

#ifndef KMEANSII_EXPERIMENT_ANALYZER2_H
#define KMEANSII_EXPERIMENT_ANALYZER2_H

#include <unordered_map>
#include <cassert>
#include "../algorithm/kmeans_data.h"
#include "../algorithm/kmeans_helpers.h"
#include "experiment_result.h"
#include "perfect_matching_uncompleted_deprecated.h"
#include "centre_intersections.h"
#include "experiments_bipartite_perfect_matching.h"
#include "experiment_helpers.h"

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
      std::function<double(std::pair<size_t, size_t>)> calcVal = [&](std::pair<size_t, size_t> p)->double {
        size_t result = std::get<0>(p);
        assert(result < std::numeric_limits<double>::max());
        return (double) result;
      };
      helpers::mergeSort(matchingPairs, calcVal);

      /*TODO:
       * This is a super hacky way where I sort the patching pairs in terms of their first value.
       * Then I create a vector of pairs adding each of the matching pairs to the centre.
       * Then I resport the centres in terms of the second value of the matching pairs.
       * This in turn should give us the centres matching properly, but is super hacky because we have to
       * copy the centres more than once. This should be avoided somehow.
       *
       */

      std::vector<std::pair<std::pair<size_t, size_t>, Instance>> tempResult;
      assert(matchingPairs.size() == experimentResults_[experimentId].centres.size());
      for(size_t centreId = 0; centreId < matchingPairs.size(); ++centreId) {
        tempResult.push_back(
            std::make_pair(matchingPairs[centreId], experimentResults_[experimentId].centres[centreId]));
      }
      std::function<double(std::pair<std::pair<size_t, size_t>, Instance>)> calcVal2 = [](
          std::pair<std::pair<size_t, size_t>, Instance> p)->double {
        return std::get<1>(std::get<0>(p));
      };
      helpers::mergeSort(tempResult, calcVal2);
      experimentResults_[experimentId].centres.clear();
      for(std::pair<std::pair<size_t, size_t>, Instance> r:tempResult) {
        experimentResults_[experimentId].centres.push_back(std::get<1>(r));
      }
    }
  }

  void calculatePointPositions() {
    for(size_t experimentId = 0; experimentId < experimentResults_.size(); ++experimentId) {
      for(size_t instanceId = 0; instanceId < dataset_.size(); ++instanceId) {
        pointPositions_[experimentId][instanceId] = ::kmeans::helpers::findBelongingCentrePosition(dataset_[instanceId],
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

  void validateDataset() {
    assert(dataset_.size() > 0);
    size_t k = experimentResults_[0].centres.size();
    assert(dataset_.size() > k);
    for(
      const auto &er:experimentResults_
        ) {
      assert(er.centres.size() == k);
    }
  }

  void validateExperiments() {
    assert(experimentResults_.size() > 1);
    if(experimentResults_.
        size()
       % 2 == 1) {
      experimentResults_.resize(experimentResults_.size() - 1);
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

    validateExperiments();
    validateDataset();

    populatePointMaps(); //not sure if we need this.
    reorderExperimentCentres();
    calculatePointPositions();
    calculateIntersections();
  }


};
}//namespace experiments
}//namespae kmeans

#endif //KMEANSII_EXPERIMENT_ANALYZER2_H
