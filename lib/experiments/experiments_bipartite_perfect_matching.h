//
// Created by Yaser Alkayale on 2017-07-22.
//

#ifndef KMEANSII_HUNGARIAN_H
#define KMEANSII_HUNGARIAN_H

#include <vector>
#include <queue>
#include <limits>
#include <cassert>
#include "experiments_data.h"


namespace kmeans{
namespace experiments{

struct RightVertex;
struct LeftVertex;

class LeftVertex{
public:
  std::size_t name_;
  RightVertex *parent_;
  double potential_;
  bool isExplored_ = false;

  LeftVertex(std::size_t name) : name_(name), parent_(nullptr), potential_(0) {}
  void reset() { parent_ = nullptr; }

  bool isExplored() { return parent_ != nullptr || isExplored_; }

};

class RightVertex : public LeftVertex{
public:
  LeftVertex *match_;
  double slack_;
  LeftVertex *parent_;

  RightVertex(std::size_t name) : LeftVertex(name), match_(nullptr), slack_(0) {};
  bool isMatched() { return match_ != nullptr; }
  void reset() {
    LeftVertex::reset();
    slack_ = std::numeric_limits<double>::max();
  }
};

class Hungarian{
private:
  const Matrix<double> &matrix_;
  std::queue<LeftVertex *> q_;
  std::vector<LeftVertex> left_;
  std::vector<RightVertex> right_;

public:
  Hungarian(const Matrix<double> &matrix);

  void startPhase(LeftVertex &leftVertex);

  double slack(const LeftVertex &leftVertex, const RightVertex &rightVertex);

  RightVertex *exploreRightVertex(RightVertex &v);

  RightVertex *exploreTightEdgesFrom(LeftVertex &u);

  RightVertex *exploreTightEdges();

  RightVertex *adjustPotentials();

  RightVertex *findAugmentingPathFrom(LeftVertex &leftVertex);

  void augmentMatching(RightVertex *tail);

  std::vector<std::pair<std::size_t, std::size_t>> solve();
};


std::vector<std::pair<std::size_t, std::size_t>> minimumWeightPerfectMatching(const Matrix<double> &m);


}//namespace experiments
}//namespace kmeans
#endif //KMEANSII_HUNGARIAN_H
