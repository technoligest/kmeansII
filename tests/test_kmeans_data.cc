//
// Created by Yaser Alkayale on 2017-07-12.
//
#include "catch.hpp"
#include "../lib/Algorithm/kmeans_data.h"

TEST_CASE("operator/= works for instance divided by a vector of size_t") {
  kmeans::Instance instance1;
  std::vector<size_t> sizes;
  kmeans::Instance result;
  using kmeans::operator/=;
  SECTION("Dividing an empty instance works.") {
    instance1 /= sizes;
    REQUIRE(instance1 == result);
  }
  SECTION("Dividing 1 item by 1 works.") {
    instance1 = {1};
    sizes = {1};
    result = {1};
    instance1 /= sizes;
    REQUIRE(instance1 == result);
    sizes = {2};
    instance1 /= sizes;
    result = {0.5};
    REQUIRE(instance1 == result);
  }
  SECTION("Dividing 2 item lists works.") {
    instance1 = {2, 2, 2};
    sizes = {2, 2, 2};
    instance1 /= sizes;
    result = {1, 1, 1};
    REQUIRE(instance1 == result);
    instance1 = {15, 15, 15};
    instance1 /= sizes;
    result = {7.5, 7.5, 7.5};
    REQUIRE(instance1 == result);
  }
  SECTION("Dividing negative instance.") {
    instance1 = {-4, 12, -18, 0};
    sizes = {4, 4, 9, 12};
    instance1 /= sizes;
    result = {-1, 3, -2, 0};
    REQUIRE(instance1 == result);
  }
}