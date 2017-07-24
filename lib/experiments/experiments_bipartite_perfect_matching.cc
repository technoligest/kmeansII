//
// Created by Yaser Alkayale on 2017-07-22.
//


#include "experiments_bipartite_perfect_matching.h"

namespace kmeans{
namespace experiments{
namespace{
void checkValidMatrix(const Matrix<double> &matrix) {
  size_t n = matrix.size();
  assert(n > 0);
  for(const auto &row:matrix) {
    assert(row.size() == n);
  }
}
}//namespace anonymous

std::vector<std::pair<std::size_t, std::size_t>> minimumWeightPerfectMatching(const Matrix<double> &m) {
  checkValidMatrix(m);
  Hungarian h(m);
  return h.solve();
}

Hungarian::Hungarian(const Matrix<double> &matrix) : matrix_(matrix) {
  std::size_t n = matrix_.size();
  for(std::size_t i = 0; i < n; ++i) {
    left_.push_back(LeftVertex(i));
    right_.push_back(RightVertex(i));
  }
}

std::vector<std::pair<std::size_t, std::size_t>> Hungarian::solve() {
  for(auto &u:left_) {
    RightVertex *tail = findAugmentingPathFrom(u);
    //int i=10+2;
    augmentMatching(tail);
  }
  std::vector<std::pair<std::size_t, std::size_t>> result;
  for(const auto &item:right_) {
    result.push_back({item.match_->name_, item.name_});
  }
  return result;
}

RightVertex *Hungarian::findAugmentingPathFrom(LeftVertex &leftVertex) {
  startPhase(leftVertex);
  while(true) {
    auto tail = exploreTightEdges();
    if(tail == nullptr) { tail = adjustPotentials(); }
    if(tail != nullptr) { return tail; }
  }
}

void Hungarian::startPhase(LeftVertex &leftVertex) {
  for(auto &vertex:left_) {
    vertex.reset();
  }
  for(auto &vertex:right_) {
    vertex.reset();
  }
  leftVertex.parent_ = nullptr;//TODO:&leftVertex;
  leftVertex.isExplored_ = true;//TODO:
  while(!q_.empty()) { q_.pop(); }
  q_.push(&leftVertex);
}

RightVertex *Hungarian::exploreTightEdges() {
  while(!q_.empty()) {
    RightVertex *tail = exploreTightEdgesFrom(*q_.front());
    q_.pop();
    if(tail != nullptr) return tail;
  }
  return nullptr;
}

RightVertex *Hungarian::exploreTightEdgesFrom(LeftVertex &u) {
  for(auto &v: right_) {
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

RightVertex *Hungarian::adjustPotentials() {
  double minSlack = std::numeric_limits<double>::max();
  for(auto &v:right_) {
    if(!v.isExplored()) {
      minSlack = std::min(minSlack, v.slack_);
    }
  }
  for(auto &u:left_) {
    if(u.isExplored()) {
      u.potential_ += minSlack;
    }
  }
  for(auto &v:right_) {
    if(v.isExplored()) {
      v.potential_ -= minSlack;
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

RightVertex *Hungarian::exploreRightVertex(RightVertex &v) {
  if(!v.isMatched()) { return &v; }

  v.match_->parent_ = &v;
  q_.push(v.match_);
  return nullptr;
}

double Hungarian::slack(const LeftVertex &leftVertex, const RightVertex &rightVertex) {
  return matrix_[leftVertex.name_][rightVertex.name_] - leftVertex.potential_ - rightVertex.potential_;
}
void Hungarian::augmentMatching(RightVertex *tail) {
  LeftVertex *v = tail->parent_;
  while(true) {
    tail->match_ = v;

    if(v->parent_ == nullptr || v->parent_->parent_ == nullptr) {
      break;
    }
    tail = v->parent_;
    v = tail->parent_;
  }
  //static_cast<RightVertex *>(vector[i + 1])->match_ = vector[i];
}


}//namespace experiments
}//namespace kmeans
