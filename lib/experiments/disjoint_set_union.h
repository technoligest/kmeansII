//
// Created by Yaser Alkayale on 2017-07-15.
//

#ifndef KMEANSII_DISJOINT_SET_UNION_H
#define KMEANSII_DISJOINT_SET_UNION_H

#include <unordered_map>
#include "../algorithm/kmeans_data.h"

namespace kmeans{
namespace experiments{

struct SetNode{
  SetNode *parent_;
  ull id_;
  ull num_children_;

  SetNode(SetNode *parent, ull id, ull num_children) : parent_(parent), id_(id), num_children_(num_children) {}
};

class DisjointSet{
protected:
  std::unordered_map<ull, SetNode> nodeMap;

public:
  inline void makeSet(const ull &instId) {
    if(nodeMap.find(instId) == nodeMap.end()) {
      nodeMap.insert({instId, SetNode(nullptr, instId, 0)});
    }
  }

  inline bool unionSets(SetNode &node1, SetNode &node2) {
    auto node1parent = node1.parent_;
    auto node2parent = node2.parent_;
    if(node1parent == node2parent) { return false; }
    if(node1parent->num_children_ > node2parent->num_children_) {
      node1parent->num_children_ += node2parent->num_children_ + 1;
      node2parent->parent_ = node1parent;
    } else {
      node2parent->num_children_ += node1parent->num_children_ + 1;
      node1parent->parent_ = node1parent;
    }
    return true;
  }

  inline bool unionSets(const ull &inst1Id, const ull &inst2Id) {
    auto node1 = nodeMap.find(inst1Id);
    auto node2 = nodeMap.find(inst2Id);
    if(node1 == nodeMap.end() || node2 == nodeMap.end()) { return false; }
    return unionSets((*node1).second, (*node2).second);
  }

  inline SetNode *findSet(const ull &instId) {
    auto node = nodeMap.find(instId);
    if(node != nodeMap.end()) {
      return nullptr;
    }
    return findSet((*node).second);
  }

  inline SetNode *findSet(SetNode &node) {
    if(node.parent_ == nullptr) {
      return &node;
    }
    node.parent_ = findSet(*node.parent_);
    return node.parent_;
  }
};//class disjointset

class KmeansDisjointSet : public DisjointSet{
private:
  const DatasetIds ids_;

  void createDisjointSet() {
    if(ids_.size() == 0)return;
    if(ids_.size() == 1) {
      makeSet(ids_[0]);
      return;
    }
    for(size_t i = 1; i < ids_.size(); ++i) {
      makeSet(ids_[i]);
      unionSets(ids_[i - 1], ids_[i]);
    }
  }

public:
  KmeansDisjointSet(const DatasetIds &ids) : ids_(ids) {}

  ull getUnionSize() {
    if(ids_.empty())return 0;
    return findSet(ids_[0])->num_children_ + 1;
  }

};

}//namespace experiments
}//namespace kmeans



#endif //KMEANSII_DISJOINT_SET_UNION_H
