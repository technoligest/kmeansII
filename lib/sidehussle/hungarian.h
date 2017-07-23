//
// Created by Yaser Alkayale on 2017-07-22.
//

#ifndef KMEANSII_HUNGARIAN_H
#define KMEANSII_HUNGARIAN_H

#include <vector>
#include <queue>
#include <limits>
#include <cassert>

using Matrix = std::vector<std::vector<double>>;

struct RightVertex;

class LeftVertex{
public:
  std::size_t name_;
  LeftVertex *parent_;
  double potential;

  LeftVertex(std::size_t name) : name_(name), parent_(nullptr), potential(0) {}
  void reset() { parent_ = nullptr; }
  bool isExplored() { return parent_ != nullptr; }

};

class RightVertex : public LeftVertex{
public:
  LeftVertex *match_;
  double slack_;

  RightVertex(std::size_t name) : LeftVertex(name), match_(nullptr), slack_(0) {};
  bool isMatched() { return match_ != nullptr; }
  void reset() {
    LeftVertex::reset();
    slack_ = std::numeric_limits<double>::max();
  }
};

class Hungarian{
private:
  const Matrix &matrix_;
  std::queue<LeftVertex *> q_;
  std::vector<LeftVertex> left_;
  std::vector<RightVertex> right_;
public:
  Hungarian(const Matrix &matrix) : matrix_(matrix) {
    std::size_t n = matrix_.size();
    for(std::size_t i = 0; i < n; ++i) {
      left_.push_back(LeftVertex(i));
      right_.push_back(RightVertex(i));
    }
  }

  void startPhase(LeftVertex &leftVertex);

  double slack(const LeftVertex &leftVertex, const RightVertex &rightVertex);

  LeftVertex *exploreRightVertex(RightVertex &v);

  LeftVertex *exploreTightEdgesFrom(LeftVertex &u);

  LeftVertex *exploreTightEdges();

  LeftVertex *adjustPotentials();

  std::vector<LeftVertex *> pathGenerator(LeftVertex *v);

  std::vector<LeftVertex *> findAugmentingPathFrom(LeftVertex &leftVertex);

  void augmentMatching(std::vector<LeftVertex *> &vector);

  std::vector<std::pair<std::size_t, std::size_t>> solve();
};

inline auto minimumWeightPerfectMatching(const Matrix &m) {
  Hungarian h(m);
  return h.solve();
}
#endif //KMEANSII_HUNGARIAN_H
