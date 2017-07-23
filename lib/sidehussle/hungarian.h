//
// Created by Yaser Alkayale on 2017-07-22.
//

#ifndef KMEANSII_HUNGARIAN_H
#define KMEANSII_HUNGARIAN_H

#include <vector>
#include <queue>

using Matrix = std::vector<std::vector<double>>;

struct RightVertex;

class LeftVertex{
public:
  size_t name_;
  RightVertex *parent_;
  double potential;

  LeftVertex(size_t name) : name_(name), parent_(nullptr), potential(0) {}

  void reset() {
    parent_ = nullptr;
  }

  bool isExplored() {
    return parent_ != nullptr;
  }
};

class RightVertex : public LeftVertex{
public:
  LeftVertex *match_;
  double slack_;

  RightVertex(size_t name) : LeftVertex(name), match_(nullptr), slack_(0) {};

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
    auto n = matrix_.size();
    for(size_t i = 0; i < n; ++i) {
      left_.push_back(LeftVertex(i));
      right_.push_back(RightVertex(i));
    }
  }

  void startPhase(LeftVertex &leftVertex) {
    for(auto &vertex:left_) {
      vertex.reset();
    }
    for(auto &vertex:right_) {
      vertex.reset();
    }
    leftVertex.parent_ = &leftVertex;
    while(!q_.empty()) { q_.pop(); }
    q_.push(&leftVertex);
  }

  double slack(const LeftVertex &leftVertex, const RightVertex &rightVertex) {
    return matrix_[leftVertex.name_][rightVertex.name_] - leftVertex.potential - rightVertex.potential;
  }

  LeftVertex *exploreRightVertex(RightVertex &v) {
    if(v.isMatched()) {
      v.match_->parent_ = &v;
      q_.push(v.match_);
      return nullptr;
    }
    return &v;
  }

  LeftVertex *exploreTightEdgesFrom(LeftVertex &u) {
    for(auto v: right_) {
      if(v.isExplored())continue;
      auto uvSlack = slack(u, v);
      if(uvSlack == 0) {
        v.parent_ = &u;
        auto tail = exploreRightVertex(v);
        if(tail != nullptr) return tail;
      } else {
        v.slack_ = std::min(v.slack_, uvSlack);
      }
    }
    return nullptr;
  }

  LeftVertex *exploreTightEdges() {
    while(!q_.empty()) {
      LeftVertex *tail = exploreTightEdgesFrom(*q_.front());
      if(tail != nullptr) return tail;
    }
    return nullptr;
  }

  LeftVertex *adjustPotentials() {
    double minSlack = std::numeric_limits<double>::max();
    for(auto &v:right_) {
      if(!v.isExplored()) {
        minSlack = std::min(minSlack, v.slack_);
      }
    }
    for(auto &u:left_) {
      if(u.isExplored()) {
        u.potential += minSlack;
      }
    }
    for(auto &v:right_) {
      if(v.isExplored()) {
        v.potential -= minSlack;
        continue;
      }
      v.slack_ -= minSlack;
      if(v.slack_ != 0) { continue; }
      for(auto &w:left_) {
        if(w.isExplored() && slack(w, v) == 0) {
          v.parent_ = &w;
          break;
        }
      }

      auto tail = exploreRightVertex(v);
      if(tail != nullptr) { return tail; }
    }
    return nullptr;
  }

  auto findAugmentingPathFrom(LeftVertex &leftVertex) {
    startPhase(leftVertex);
    while(true) {
      auto tail = exploreTightEdges();
      if(tail == nullptr) {
        tail = adjustPotentials();
      }
      if(tail != nullptr) {
        return pathGenerator(tail);
      }
    }
  }

  std::vector<std::pair<size_t, size_t>> solve() {
    for(auto u:left_) {
      auto path = findAugmentingPathFrom(u);
      augmentMatching(path);
    }
    std::vector<std::pair<size_t, size_t>> result;
    for(auto item:right_) {
      result.push_back({item.match_->name_, item.name_});
    }
    return result;
  }
};

auto minimumWeightPerfectMatching(const Matrix &m) {
  Hungarian h(m);
  return h.solve();
}


#endif //KMEANSII_HUNGARIAN_H
