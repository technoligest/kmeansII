//
// Created by Yaser Alkayale on 2017-07-14.
//

#ifndef KMEANSII_EXPERIMENT_HELPERS_H
#define KMEANSII_EXPERIMENT_HELPERS_H

#include "../algorithm/kmeans.h"

namespace kmeans{
namespace experiments{
namespace helpers{

void heapSort(std::vector<size_t> &arr);

template<typename T>
void
merge(std::vector<T> &array, const std::function<double(T)> &val, const size_t &l, const size_t &m, const size_t &r) {
  assert(l < array.size() && m < array.size() && r < array.size());
  std::vector<T> tempLeftArray;
  std::vector<T> tempRightArray;
  for(size_t i = l; i <= m; ++i) {
    tempLeftArray.push_back(array[i]);
  }
  for(size_t i = m + 1; i <= r; ++i) {
    tempRightArray.push_back(array[i]);
  }
  size_t leftIndex = 0;
  size_t rightIndex = 0;
  size_t i = l;
  for(; leftIndex < tempLeftArray.size() && rightIndex < tempRightArray.size(); ++i) {
    assert(tempLeftArray.size() > leftIndex);
    assert(tempRightArray.size() > rightIndex);
    assert(i < array.size());
    if(val(tempLeftArray[leftIndex]) < val(tempRightArray[rightIndex])) {
      array[i] = tempLeftArray[leftIndex];
      ++leftIndex;
    } else if(val(tempLeftArray[leftIndex]) > val(tempRightArray[rightIndex])) {
      array[i] = tempRightArray[rightIndex];
      ++rightIndex;
    } else {
      array[i] = tempLeftArray[leftIndex];
      ++i;
      assert(i < array.size());
      array[i] = tempRightArray[rightIndex];
      ++leftIndex;
      ++rightIndex;
    }
  }
  for(; leftIndex < tempLeftArray.size(); ++i, ++leftIndex) {
    assert(tempLeftArray.size() > leftIndex);
    assert(i < array.size());
    array[i] = tempLeftArray[leftIndex];
  }
  for(; rightIndex < tempRightArray.size(); ++i, ++rightIndex) {
    assert(tempRightArray.size() > rightIndex);
    assert(i < array.size());
    array[i] = tempRightArray[rightIndex];
  }
  assert(i == r + 1);
  assert(leftIndex == tempLeftArray.size());
  assert(rightIndex == tempRightArray.size());
}

template<typename T>
void mergeSort(std::vector<T> &array, const std::function<double(T)> &val, const size_t &l, const size_t &r) {

  assert(l < array.size() && r < array.size());
  if(l < r) {
    size_t m = (r - l) / 2 + l;
    mergeSort(array, val, l, m);
    mergeSort(array, val, m + 1, r);
    merge(array, val, l, m, r);
  }
}


template<typename T>
void mergeSort(std::vector<T> &arr, const std::function<double(T)> &val) {
  if(arr.size() > 1) mergeSort(arr, val, 0, arr.size() - 1);
}



ull lastNumberedFile(const std::string directory, std::string prefix);

}//namespace helpers
}//namespace experiments
}//namespace kmean


#endif //KMEANSII_EXPERIMENT_HELPERS_H
