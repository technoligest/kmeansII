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

/*
 * Sort the dataset & arr it terms of the arr provided.
 * Sort in ascending order.
 */
void heapSort(Dataset &d, std::vector<double> &arr) {
  if(arr.size() == 0)return;
  size_t n = arr.size();
  for(size_t i = n / 2 - 1; ; --i) {
    heapify(d, arr, n, i);
    if(i == 0) {
      break;
    }
  }

  for(size_t i = n - 1; ; --i) {
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

void validateMatrix(const Matrix<double> &matrix) {
  assert(matrix.size() > 2);
  for(const auto &instance:matrix) {
    assert(instance.size() == 2);
  }
}

size_t findLowestLeftPointId(const Matrix<double> &dataset) {
  size_t lowestId = 0;
  for(size_t i = 1; i < dataset.size(); ++i) {
    if(dataset[i][1] < dataset[lowestId][1] ||
       (dataset[i][1] == dataset[lowestId][1] && dataset[i][0] < dataset[lowestId][0])) {
      lowestId = i;
    }
  }
  return lowestId;
}

void removeItemsWithSameAngleToFirstPoint(Matrix<double> &dataset, std::vector<double> &angleToLowestPoint) {
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
}
}//namespace anonymous

Matrix<double> calculateConvexHull(Matrix<double> dataset) {
  validateMatrix(dataset);

  std::swap(dataset[findLowestLeftPointId(dataset)], dataset[0]);

  std::vector<double> angleToLowestPoint(dataset.size(), -1);
  std::vector<double> lowestRight{dataset[0][0] + 10, dataset[0][1]};
  for(size_t itemId = 1; itemId < dataset.size(); ++itemId) {
    angleToLowestPoint[itemId] = calculateCosSquaredOfPolarAngle(dataset[0], lowestRight, dataset[itemId]);
  }
  //sort the dataset in terms of the angles to the lowest point.
  heapSort(dataset, angleToLowestPoint);

  removeItemsWithSameAngleToFirstPoint(dataset, angleToLowestPoint);

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

double convexHullArea(const Matrix<double> &dataset) {
  std::size_t size = dataset.size();
  if(size < 3) return 0;
  double result = 0;
  assert(dataset[0].size() == 2);
  for(std::size_t rowId = 0; rowId < size - 1; ++rowId) {
    assert(dataset[rowId + 1].size() == 2);
    result += dataset[rowId][0] * dataset[rowId + 1][1] - dataset[rowId][1] * dataset[rowId + 1][0];
  }
  result += dataset[size - 1][0] * dataset[0][1] - dataset[size - 1][1] * dataset[0][0];

  return result / 2;
}

}//namespace experiments
}//namespace kmeans