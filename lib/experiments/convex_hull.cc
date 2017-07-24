//
// Created by Yaser Alkayale on 2017-07-19.
//

#include <cassert>
#include <cmath>
#include "../algorithm/kmeans_helpers.h"

namespace kmeans{
namespace experiments{

namespace{
void heapify(Dataset &d, std::vector<double> &arr, size_t n, size_t i) {
  size_t largest = i;  // Initialize largest as root
  size_t l = 2 * i + 1;  // left = 2*i + 1
  size_t r = 2 * i + 2;  // right = 2*i + 2

  if(l < n && arr[l] > arr[largest])
    largest = l;

  if(r < n && arr[r] > arr[largest])
    largest = r;

  if(largest == i) return;

  std::swap(arr[i], arr[largest]);
  std::swap(d[i], d[largest]);

  // Recursively heapify the affected sub-tree
  heapify(d, arr, n, largest);
}

void heapSort(Dataset &d, std::vector<double> &arr) {
  if(arr.size() == 0)return;
  size_t n = arr.size();
  for(size_t i = n / 2 - 1; i >= 0; --i) {
    heapify(d, arr, n, i);
    if(i == 0) {
      break;
    }
  }

  for(size_t i = n - 1; i >= 0; --i) {
    std::swap(arr[0], arr[i]);
    std::swap(d[0], d[i]);
    heapify(d, arr, i, 0);
    if(i == 0) {
      break;
    }
  }
}

/*
 * Polar angle cannot be higher than 180.
 */
double calculateCosSquaredOfPolarAngle(const Instance &origin, const Instance &instance1,
                                       const Instance &instance2) {
  assert(origin.size() == 2 && instance1.size() == 2 && instance2.size() == 2);

  return acos(((instance1[0] - origin[0]) * (instance2[0] - origin[0]) +
               ((instance1[1] - origin[1]) * (instance2[1] - origin[1]))) /
              (std::sqrt(helpers::findDistanceSquared(origin, instance2)) *
               std::sqrt(helpers::findDistanceSquared(origin, instance1)))) / 3.14159 * 180;
}

bool isLeftTurn(const Instance &rightPoint, const Instance &origin, const Instance &leftPoint) {
  assert(rightPoint.size() == 2);
  assert(origin.size() == 2);
  assert(leftPoint.size() == 2);

  return 0 > ((origin[1] - rightPoint[1]) * (leftPoint[0] - origin[0]) -
              (origin[0] - rightPoint[0]) * (leftPoint[1] - origin[1]));
}
}//namespace anonymous

Dataset calculateConvexHull(Dataset dataset) {
  assert(dataset.size() > 2);
  for(
    const auto &instance:dataset) {
    assert(instance.size() == 2);
  }

  size_t lowestId = 0;
  for(size_t i = 1; i < dataset.size(); ++i) {
    if(dataset[i][1] < dataset[lowestId][1] ||
       (dataset[i][1] == dataset[lowestId][1] && dataset[i][0] < dataset[lowestId][0])) {
      lowestId = i;
    }
  }

  std::swap(dataset[lowestId], dataset[0]);

  std::vector<double> angleToLowestPoint(dataset.size(), -1);
  std::vector<double> lowestRight{dataset[0][0] + 10, dataset[0][1]};
  for(size_t itemId = 1; itemId < dataset.size(); ++itemId) {
    angleToLowestPoint[itemId] = calculateCosSquaredOfPolarAngle(dataset[0], lowestRight, dataset[itemId]);
  }

  heapSort(dataset, angleToLowestPoint);
  for(size_t itemId = 1; itemId < dataset.size(); ++itemId) {
    if(fabs(angleToLowestPoint[itemId] - angleToLowestPoint[itemId - 1]) < 1e-4) {
      if(helpers::findDistanceSquared(dataset[0], dataset[itemId]) <
         helpers::findDistanceSquared(dataset[0], dataset[itemId - 1])) {
        dataset.erase(dataset.begin() + itemId);
        angleToLowestPoint.erase(angleToLowestPoint.begin() + itemId);
      } else {
        dataset.erase(dataset.begin() + itemId - 1);
        angleToLowestPoint.erase(angleToLowestPoint.begin() + itemId - 1);
      }
      --itemId;
    }
  }

  Dataset result = {dataset[0], dataset[1], dataset[2]};
  for(size_t i = 3; i < dataset.size(); ++i) {
    while(!isLeftTurn(result[result.size() - 2], result[result.size() - 1], dataset[i])) {
      result.pop_back();
    }
    result.push_back(dataset[i]);
  }

  assert(result.size() > 2);
  return result;
}

}//namespace experiments
}//namespace kmeans