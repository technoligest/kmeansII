//
// Created by Yaser Alkayale on 2017-07-24.
//

#include "catch.hpp"
#include "../lib/experiments/experiment_helpers.h"

TEST_CASE("mergeSort with given function works properly") {
  using namespace kmeans::experiments::helpers;
  using std::vector;
  vector<double> inputVector{};
  std::function<double(double)> valueFunc = [&](size_t l)->double { return l; };

  mergeSort(inputVector, valueFunc);
  vector<double> resultVector{};
  REQUIRE(inputVector == resultVector);

  inputVector = {1, 2, 3};
  resultVector = {1, 2, 3};
  mergeSort(inputVector, valueFunc);
  REQUIRE(inputVector == resultVector);

  inputVector = {3,2,1};
  mergeSort(inputVector,valueFunc);
  REQUIRE(inputVector==resultVector);
}