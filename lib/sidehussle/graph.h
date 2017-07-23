//
// Created by Yaser Alkayale on 2017-07-21.
//

#ifndef KMEANSII_GRAPH_H
#define KMEANSII_GRAPH_H

#include <vector>
#include <typeinfo>
#include <iostream>
#include <unordered_map>
#include <queue>

namespace data{//TODO rename this namespace
template<typename T>
class BipartiteGraph{
private:
  std::vector<std::vector<T>> matrix_;
  std::function<bool(T val)> isConnected_;
public:
  std::vector<T> &operator[](const size_t &i) {
    return matrix_[i];
  }

  inline BipartiteGraph(const size_t &rows, const size_t &cols) : matrix_(
      std::vector<T>(rows, std::vector<T>(cols, 0))), isConnected_([](T val)->bool { return val > 0; }) {}

  inline BipartiteGraph(std::vector<std::vector<T>> matrix,
                        std::function<bool(T)> isConnected = [](T val)->bool { return true; }) : matrix_(matrix),
                                                                                                  isConnected_(
                                                                                                      isConnected) {}

  inline size_t size() { return matrix_.size(); }

  inline void breadthFirstSearch(const std::function<bool()> &stopHere) {
    std::unordered_map<size_t, bool> seen;
    std::queue<size_t> q;
    for(size_t n = 0; n < matrix_.size() * 2; ++n) {
      seen.insert({n, false});
    }
    q.push(0);
    while(q.empty()) {
      size_t popped = q.front();
      q.pop();
      if(seen[popped]) continue;
      seen[popped] = true;

      std::cout << popped << std::endl;
      if(popped < matrix_.size()) {
        for(size_t colId = 0; colId < matrix_[popped].size(); ++colId) {
          if(isConnected_(matrix_[popped][colId]) && !seen[colId + matrix_.size()]) {
            q.push(colId + matrix_.size());
          }
        }
      } else {
        for(size_t rowId = 0; rowId < matrix_.size(); ++rowId) {
          if(isConnected_(matrix_[rowId][popped]) && !seen[rowId]) {
            q.push(rowId);
          }
        }
      }
    }
  }

  inline void depthFirstSearch(const std::function<bool()> &stopHere) {

  }
};
}




#endif //KMEANSII_GRAPH_H
