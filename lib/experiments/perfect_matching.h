//
// Created by Yaser Alkayale on 2017-07-18.
//

#ifndef KMEANSII_PERFECTMATCHING_H
#define KMEANSII_PERFECTMATCHING_H

#include <cassert>
#include "../algorithm/kmeans_data.h"

namespace kmeans{
namespace experiments{
class PerfectMatching{
private:
  Matrix<Distance> distanceMatrix_;
  std::vector<int> perfectMatchingResult_;

  Distance findMinInRow(const size_t &i) {
    Distance result = std::numeric_limits<Distance>::max();
    for(const auto &item:distanceMatrix_[i]) {
      if(item < result) {
        result = item;
      }
    }
    return result;
  }

  Distance findMinInCol(const size_t &i) {
    Distance result = std::numeric_limits<Distance>::max();
    for(size_t rowId = 0; rowId < distanceMatrix_.size(); ++rowId) {
      if(distanceMatrix_[rowId][i] < result)
        result = distanceMatrix_[rowId][i];
    }
    return result;
  }

  void subtractFromRow(const size_t &rowId, const Distance &d) {
    for(size_t colId = 0; colId < distanceMatrix_[rowId].size(); ++colId) {
      distanceMatrix_[rowId][colId] -= d;
    }
  }

  void subtractFromCol(const size_t &colId, const Distance &d) {
    for(size_t rowId = 0; rowId < distanceMatrix_.size(); ++rowId) {
      distanceMatrix_[colId][rowId] -= d;
    }
  }

  bool findMaximumNumBarpartiteMatchings(const size_t &rowId, std::vector<bool> &seen, std::vector<int> &matchings) {
    assert(rowId < distanceMatrix_.size());
    for(size_t colId = 0; colId < distanceMatrix_[rowId].size(); ++colId) {
      if(distanceMatrix_[rowId][colId] == 0 && !seen[colId]) {
        seen[colId] = true;
        if(matchings[colId] < 0 || findMaximumNumBarpartiteMatchings(matchings[colId], seen, matchings)) {
          matchings[colId] = rowId;
          return true;
        }
      }
    }
    return false;
  }

  bool findMaximumNumBarpartiteMatchings(const size_t &rowId, std::vector<int> &matchings) {
    assert(rowId < distanceMatrix_.size());
    std::vector<bool> seen(distanceMatrix_[rowId].size(), false);
    return findMaximumNumBarpartiteMatchings(rowId, seen, matchings);
  }

  ull findMaximumNumBirpartiteMatchings(std::vector<int> &matchings) {
    if(distanceMatrix_.empty()) {
      matchings.clear();
      return 0;
    }
    size_t firstColumnSize = distanceMatrix_[0].size();
    for(const auto &row:distanceMatrix_) {
      assert(row.size() == firstColumnSize);
    }
    ull result = 0;
    matchings = std::vector<int>(distanceMatrix_.size(), -1);
    for(size_t rowId = 0; rowId < distanceMatrix_.size(); ++rowId) {
      if(findMaximumNumBarpartiteMatchings(rowId, matchings)) {
        ++result;
      }
    }
    assert(result <= distanceMatrix_.size());
    return result;
  }
  void confirmProperInputMatrix() {
    auto size = distanceMatrix_.size();
    assert(size != 0 && size % 2 == 0);
    for(const auto &row:distanceMatrix_) {
      assert(row.size() == size);
    }
    //for(size_t rowId = 0; rowId < size; ++rowId) {
    //  for(size_t columnId = 0; columnId < size; ++columnId) {
    //    assert(distanceMatrix_[rowId][columnId] == distanceMatrix_[columnId][rowId]);
    //  }
    //}
  }
public:
  PerfectMatching(Matrix<Distance> distanceMatrix) : distanceMatrix_(distanceMatrix) {

    confirmProperInputMatrix();
  };

  std::vector<int> runAlgorithm() {
    for(size_t i = 0; i < distanceMatrix_.size(); ++i) {
      subtractFromRow(i, findMinInRow(i));

    }
    for(size_t i = 0; i < distanceMatrix_.size(); ++i) {
      subtractFromCol(i, findMinInCol(i));
    }
    std::cout << "Cool: " << findMaximumNumBirpartiteMatchings(perfectMatchingResult_) << std::endl;
    assert(findMaximumNumBirpartiteMatchings(perfectMatchingResult_) == distanceMatrix_.size());
    return perfectMatchingResult_;
  }
};
}//namespace experiments
}//namespace kmneas

#endif //KMEANSII_PERFECTMATCHING_H
