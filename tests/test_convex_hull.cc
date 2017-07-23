//
// Created by Yaser Alkayale on 2017-07-19.
//

#include "catch.hpp"
#include "../lib/experiments/convex_hull.h"

TEST_CASE("Convex hull works.") {
  kmeans::Dataset d = {{1,  1},
                       {2,  2},
                       {3,  3},
                       {4,  4},
                       {5,  5},
                       {2,  2},
                       {2,  5},
                       {1,  10},
                       {10, 1}};
  kmeans::Dataset expectedResult = {{1,  1},
                                    {10, 1},
                                    {1,  10}};
  kmeans::Dataset result;
  result = kmeans::experiments::calculateConvexHull(d);
  REQUIRE(expectedResult == result);

  d = {{0, 0},
       {0, 1},
       {0, 2},
       {0, 3},
       {1, 1}};
  expectedResult = {{0, 0},
                    {1, 1},
                    {0, 3}};
  result = kmeans::experiments::calculateConvexHull(d);
  REQUIRE(expectedResult == result);

  d = {{0, 0},
       {1, 0},
       {1, 1},
       {1, 2},
       {1, 3},
       {0, 2}};
  expectedResult = {{0, 0},
                    {1, 0},
                    {1, 3},
                    {0, 2}};
  result = kmeans::experiments::calculateConvexHull(d);
  REQUIRE(expectedResult == result);

  d = {{1, 0},
       {1, 1},
       {1, 2},
       {1, 3},
       {0, 0}};
  expectedResult = {{0, 0},
                    {1, 0},
                    {1, 3}};
  result = kmeans::experiments::calculateConvexHull(d);
  REQUIRE(expectedResult == result);

}