//
// Created by Yaser Alkayale on 2017-07-19.
//

#include "catch.hpp"
#include "../lib/experiments/convex_hull.h"

TEST_CASE("sorting works twice") {
  //std::vector<double> toSort{5, 4, 3, 2, 1};
  //std::vector<std::vector<double>> dataset{toSort.size(), std::vector<double>()};
  //kmeans::experiments::heapSort(dataset, toSort);
  //std::vector<double> sorted{1, 2, 3, 4, 5};
  //REQUIRE(toSort == sorted);
  //
  //toSort = {1, 2, 3, 4, 5};
  //kmeans::experiments::heapSort(dataset, toSort);
  //REQUIRE(toSort == sorted);
  //
  //toSort = {5, 4, 3, 2, 1};
  //kmeans::experiments::heapSort(dataset, toSort);
  //REQUIRE(toSort == sorted);
  //
  //toSort = {1, 4, 2, 3, 5};
  //kmeans::experiments::heapSort(dataset, toSort);
  //REQUIRE(toSort == sorted);
  //
  //sorted = {-0.5, 0, 12, 17};
  //toSort = {12, -0.5, 0, 17};
  //kmeans::experiments::heapSort(dataset, toSort);
  //REQUIRE(toSort == sorted);
  //
  //toSort = {12, 0, -0.5, 17};
  //kmeans::experiments::heapSort(dataset, toSort);
  //REQUIRE(toSort == sorted);
  //
  //toSort = {};
  //sorted = {};
  //kmeans::experiments::heapSort(dataset, toSort);
  //REQUIRE(toSort == sorted);
}

TEST_CASE("Calculate polar angle works.") {
  //kmeans::Instance origin{0, 0};
  //kmeans::Instance instance1{10, 0};
  //kmeans::Instance instance2{10, 0};
  //
  //auto i = kmeans::experiments::calculateCosSquaredOfPolarAngle(origin, instance1, instance2);
  //REQUIRE(i == 0);
  //
  //instance1 = {1, 10};
  //instance2 = {0, 10};
  //i = kmeans::experiments::calculateCosSquaredOfPolarAngle(origin, instance1, instance2);
  //std::cout << i << std::endl;
  ////REQUIRE(i == 0);
  //
  //instance1 = {2, 10};
  //instance2 = {0, 1};
  //i = kmeans::experiments::calculateCosSquaredOfPolarAngle(origin, instance1, instance2);
  //std::cout << i << std::endl;
  ////REQUIRE(i == 0);
  //
  //instance1 = {3, 10};
  //i = kmeans::experiments::calculateCosSquaredOfPolarAngle(origin, instance1, instance2);
  //std::cout << i << std::endl;
  ////REQUIRE(i == 0);
  //
  //instance1 = {4, 10};
  //i = kmeans::experiments::calculateCosSquaredOfPolarAngle(origin, instance1, instance2);
  //std::cout << i << std::endl;
  ////REQUIRE(i == 0);
  //
  //instance1 = {10, 10};
  //i = kmeans::experiments::calculateCosSquaredOfPolarAngle(origin, instance1, instance2);
  //std::cout << i << std::endl;
  //REQUIRE(fabs(i - 45) < 1e-2);
  //
  //instance1 = {10, 0};
  //i = kmeans::experiments::calculateCosSquaredOfPolarAngle(origin, instance1, instance2);
  //std::cout << i << std::endl;
  //REQUIRE(fabs(i - 90) < 1e-2);
  //
  //instance1 = {0, -10};
  //i = kmeans::experiments::calculateCosSquaredOfPolarAngle(origin, instance1, instance2);
  //std::cout << i << std::endl;
  //REQUIRE(fabs(i - 180) < 1e-2);
  //
  //kmeans::Instance tempInst{1, 1};
  //kmeans::Instance tempInst2{2, 1};
  //kmeans::Instance tempInst3{2, 2};
  //REQUIRE(fabs(kmeans::experiments::calculateCosSquaredOfPolarAngle(tempInst, tempInst2, tempInst3) - 45) < 1e-4);
  //
  //tempInst = {0, 0};
  //tempInst2 = {1, 0};
  //tempInst3 = {-1, 0};
  //REQUIRE(fabs(kmeans::experiments::calculateCosSquaredOfPolarAngle(tempInst, tempInst2, tempInst3) - 180) < 1e-3);
  //
  //tempInst = {0, 0};
  //tempInst2 = {1, 0};
  //tempInst3 = {0, -1};
  //REQUIRE(fabs(kmeans::experiments::calculateCosSquaredOfPolarAngle(tempInst, tempInst2, tempInst3) - 90) < 1e-3);
  //
  //
  //tempInst = {0, 0};
  //kmeans::Instance rightPoint = {0, 1};
  //kmeans::Instance leftPoint = {-1, 0};
  //REQUIRE(!kmeans::experiments::isLeftTurn(rightPoint, tempInst, leftPoint));
  ////instance1 = {10, 2};
  ////std::cout << kmeans::experiments::calculateCosSquaredOfPolarAngle(origin, instance1, instance2) << std::endl;
}