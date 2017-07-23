//
// Created by Yaser Alkayale on 2017-07-22.
//


#include "hungarian.h"


std::vector<std::pair<std::size_t, std::size_t>> Hungarian::solve() {
  for(auto &u:left_) {
    std::vector<LeftVertex *> path = findAugmentingPathFrom(u);
    augmentMatching(path);
  }
  std::vector<std::pair<std::size_t, std::size_t>> result;
  for(const auto &item:right_) {
    result.push_back({item.match_->name_, item.name_});
  }
  return result;
}

std::vector<LeftVertex *> Hungarian::findAugmentingPathFrom(LeftVertex &leftVertex) {
  startPhase(leftVertex);
  while(true) {
    auto tail = exploreTightEdges();
    if(tail == nullptr) { tail = adjustPotentials(); }
    if(tail != nullptr) { return pathGenerator(tail); }
  }
}

void Hungarian::startPhase(LeftVertex &leftVertex) {
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

LeftVertex *Hungarian::exploreTightEdges() {
  while(!q_.empty()) {
    LeftVertex *tail = exploreTightEdgesFrom(*q_.front());
    q_.pop();
    if(tail != nullptr) return tail;
  }
  return nullptr;
}

LeftVertex *Hungarian::exploreTightEdgesFrom(LeftVertex &u) {
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

LeftVertex *Hungarian::adjustPotentials() {
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

LeftVertex *Hungarian::exploreRightVertex(RightVertex &v) {
  if(!v.isMatched()) { return &v; }

  v.match_->parent_ = &v;
  q_.push(v.match_);
  return nullptr;
}

double Hungarian::slack(const LeftVertex &leftVertex, const RightVertex &rightVertex) {
  return matrix_[leftVertex.name_][rightVertex.name_] - leftVertex.potential - rightVertex.potential;
}

std::vector<LeftVertex *> Hungarian::pathGenerator(LeftVertex *v) {
  std::vector<LeftVertex *> result;
  while(v != nullptr) {
    result.push_back(v);
    v = (v == v->parent_) ? nullptr : v->parent_;
  }
  return result;
}

void Hungarian::augmentMatching(std::vector<LeftVertex *> &vector) {
  for(std::size_t i = 0; i < vector.size() - 1; i += 2) {
    static_cast<RightVertex *>(vector[i + 1])->match_ = vector[i];
  }
}
