//
// Created by Yaser Alkayale on 2017-12-12.
//

#ifndef HUNGARIAN_H
#define HUNGARIAN_H

#include <vector>
#include <queue>
#include <limits>
#include <cassert>
#include "experiments_data.h"

namespace kmeans{
namespace experiments{

class RightVertex;
class LeftVertex;

class LeftVertex{
public:
  unsigned long long name_;
  RightVertex *parent_ = nullptr;
  double potential_ = 0;
  bool isExplored_ = false;

  explicit LeftVertex(std::size_t name) : name_(name) {}

  void reset();

  bool isExplored();

};

class RightVertex{
public:
  unsigned long long name_;
  LeftVertex *match_ = nullptr;
  double slack_ = 0;
  double potential_ = 0;
  LeftVertex *parent_ = nullptr;
  LeftVertex *potentialParent_ = nullptr;
  bool isExplored_ = false;

  explicit RightVertex(std::size_t name) : name_(name) {}

  bool isMatched();
  bool isExplored();
  void reset();
};

class Hungarian{
private:
  const Matrix<double> &matrix_;
  std::vector<LeftVertex *> q_;
  std::vector<LeftVertex> left_;
  std::vector<RightVertex> right_;

public:
  Hungarian(const Matrix<double> &matrix);

  void startPhase(LeftVertex *leftVertex);

  double slack(const LeftVertex &leftVertex, const RightVertex &rightVertex);

  RightVertex *exploreRightVertex(RightVertex *v);

  RightVertex *exploreTightEdgesFrom(LeftVertex *u);

  RightVertex *exploreTightEdges();

  RightVertex *adjustPotentials();

  RightVertex *findAugmentingPathFrom(LeftVertex *leftVertex);

  void augmentMatching(RightVertex *tail);

  std::vector<std::pair<std::size_t, std::size_t>> solve();
};


//Driver method where given a matrix of weights, find the pairing
std::vector<std::pair<std::size_t, std::size_t>> minimumWeightPerfectMatching(const Matrix<double> &m);


}//namespace experiments
}//namespace hungarian


#endif //IMPLEMENTATION_BIPARTITE_PERFECT_MATCHING_H
