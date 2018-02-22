//
// Created by Yaser Alkayale on 2017-07-22.
//


#include <iostream>
#include "hungarian.h"

namespace kmeans{
namespace experiments{

namespace{
//Validates that the matrix is good for processing
void checkValidMatrix(const Matrix<double> &matrix) {
  std::size_t n = matrix.size();
  assert(n > 0);
  for(const auto &row:matrix) {
    assert(row.size() == n);
  }
}
}//namespace anonymous


Hungarian::Hungarian(const Matrix<double> &matrix) : matrix_(matrix) {
  std::size_t n = matrix_.size();
  for(std::size_t i = 0; i < n; ++i) {
    left_.push_back(LeftVertex(i));
    right_.push_back(RightVertex(i));
  }
}

std::vector<std::pair<std::size_t, std::size_t>> Hungarian::solve() {
  for(auto &u:left_) {
    RightVertex *tail = findAugmentingPathFrom(&u);
    augmentMatching(tail);
  }

  std::vector<std::pair<std::size_t, std::size_t>> result;
  for(const auto &item:right_) {
    result.push_back({item.match_->name_, item.name_});
  }
  return result;
}


RightVertex *Hungarian::findAugmentingPathFrom(LeftVertex *leftVertex) {
  startPhase(leftVertex);
  while(true) {
    auto tail = exploreTightEdges();
    if(tail == nullptr) { tail = adjustPotentials(); }
    if(tail != nullptr) { return tail; }
  }
}


void Hungarian::startPhase(LeftVertex *leftVertex) {
  for(auto &vertex:left_) {
    vertex.reset();
  }
  for(auto &vertex:right_) {
    vertex.reset();
  }
  leftVertex->isExplored_ = true;//TODO:
  q_.clear();
  q_.push_back(leftVertex);
}

RightVertex *Hungarian::exploreTightEdges() {
  while(!q_.empty()) {
    auto k = q_[q_.size() - 1];
    q_.pop_back();

    RightVertex *tail = exploreTightEdgesFrom(k);

    if(tail != nullptr) return tail;
  }
  return nullptr;
}

RightVertex *Hungarian::exploreTightEdgesFrom(LeftVertex *u) {
  for(auto &v: right_) {
    if(!v.isExplored()) {
      auto uvSlack = slack(*u, v);
      if(uvSlack == 0) {
        v.parent_ = u;
        auto tail = exploreRightVertex(&v);
        if(tail != nullptr) return tail;
      } else {
        if(uvSlack < v.slack_) {
          v.slack_ = uvSlack;
          v.potentialParent_ = u;
        }
      }
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
  RightVertex *tail = nullptr;
  for(auto &v:right_) {
    if(v.isExplored()) {
      v.potential_ -= minSlack;
      continue;
    }
    v.slack_ -= minSlack;
    if(v.slack_ == 0 && tail == nullptr) {
      v.parent_ = v.potentialParent_;
      tail = exploreRightVertex(&v);
    }
  }
  return tail;
}

RightVertex *Hungarian::exploreRightVertex(RightVertex *v) {
  if(!v->isMatched()) { return v; }

  v->match_->parent_ = v;
  q_.push_back(v->match_);
  return nullptr;
}

double Hungarian::slack(const LeftVertex &leftVertex, const RightVertex &rightVertex) {
  return matrix_[leftVertex.name_][rightVertex.name_] - leftVertex.potential_ - rightVertex.potential_;
}

void Hungarian::augmentMatching(RightVertex *tail) {
  LeftVertex *v = tail->parent_;
  while(true) {
    tail->match_ = v;
    if(v->parent_ == nullptr) { break; }
    else {
      assert(v->parent_->parent_ != nullptr);
    }
    tail = v->parent_;
    v = tail->parent_;
  }
}

std::vector<std::pair<std::size_t, std::size_t>> minimumWeightPerfectMatching(const Matrix<double> &m) {
  checkValidMatrix(m);
  Hungarian h(m);
  return h.solve();
}


bool RightVertex::isMatched() {
  return match_ != nullptr;
}

bool RightVertex::isExplored() {
  return isExplored_ || parent_ != nullptr;
}

void RightVertex::reset() {
  isExplored_ = false;
  parent_ = nullptr;
  slack_ = std::numeric_limits<double>::max();
  potentialParent_ = nullptr;
}

void LeftVertex::reset() {
  isExplored_ = false;
  parent_ = nullptr;
}

bool LeftVertex::isExplored() {
  return isExplored_ || parent_ != nullptr;
}
}//namespace experiments
}//namespace kmeans
