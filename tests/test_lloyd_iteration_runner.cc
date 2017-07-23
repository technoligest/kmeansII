//
// Created by Yaser Alkayale on 2017-07-10.
//

#include "catch.hpp"
#include "../lib/algorithm/lloyd_iteration_runner.h"
/*
 * VERY IMPORTANT:
 * These test cases assume that KmeansHelpers has alreayd been thoroughly tested.
 *
 */

TEST_CASE("Test cases are working.") {
 REQUIRE(true);
}

TEST_CASE("Simple 1-d cases works for runLloyd's iteration, weights are all 1.") {
  kmeans::LloydIterationRunner l;

  kmeans::Dataset d;
  kmeans::Weights w;
  kmeans::Dataset c;

  kmeans::Dataset centreResults;

  SECTION("Same dataset and centres works") {
    w = std::vector<kmeans::Weight>(4, 1);
    d = {{1},
         {2},
         {3},
         {4}};
    c = {{1},
         {2},
         {3},
         {4}};
    centreResults = {{1},
                     {2},
                     {3},
                     {4}};
    auto dist = l.runLloydIteration(d, w, c);
    REQUIRE(c == centreResults);
    REQUIRE(dist == 0);
    REQUIRE(l.numIterations() == 1);
    dist = l.runLloydIteration(d, w, c);
    REQUIRE(c == centreResults);
    REQUIRE(dist == 0);
    REQUIRE(l.numIterations() == 2);
    dist = l.runLloydIteration(d, w, c);
    REQUIRE(c == centreResults);
    REQUIRE(dist == 0);
    REQUIRE(l.numIterations() == 3);
  }
  SECTION("Dataset inputted with correct centres works.") {
    w = std::vector<kmeans::Weight>(4, 1);
    d = {{-2},
         {-1},
         {20},
         {25}};
    c = {{-3},
         {21}};
    centreResults = {{-1.5},
                     {22.5}};
    auto dist = l.runLloydIteration(d, w, c);
    REQUIRE(c == centreResults);
    REQUIRE(dist == 22.0);
    REQUIRE(l.numIterations() == 1);
    dist = l.runLloydIteration(d, w, c);
    REQUIRE(c == centreResults);
    REQUIRE(dist == 13);
    REQUIRE(l.numIterations() == 2);
    dist = l.runLloydIteration(d, w, c);
    REQUIRE(c == centreResults);
    REQUIRE(dist == 13);
    REQUIRE(l.numIterations() == 3);
  }
  SECTION("Long one, many iterations") {
    w = std::vector<kmeans::Weight>(4, 1);
    d = {{2},
         {4},
         {15},
         {21}};
    c = {{3},
         {4}};
    double k = (40.0 / 3);
    centreResults = {{2},
                     {k}};
    auto dist = l.runLloydIteration(d, w, c);
    REQUIRE(c == centreResults);
    REQUIRE(dist == 411);
    REQUIRE(l.numIterations() == 1);

    centreResults = {{3},
                     {18}};
    dist = l.runLloydIteration(d, w, c);
    REQUIRE(c == centreResults);
    REQUIRE(fabs(dist - 65.5556) < 1e-4);
    REQUIRE(l.numIterations() == 2);

    centreResults = {{3},
                     {18}};
    dist = l.runLloydIteration(d, w, c);
    REQUIRE(c == centreResults);
    REQUIRE(dist == 20);
    REQUIRE(l.numIterations() == 3);

    centreResults = {{3},
                     {18}};
    dist = l.runLloydIteration(d, w, c);
    REQUIRE(c == centreResults);
    REQUIRE(dist == 20);
    REQUIRE(l.numIterations() == 4);

    centreResults = {{3},
                     {18}};
    dist = l.runLloydIteration(d, w, c);
    REQUIRE(c == centreResults);
    REQUIRE(dist == 20);
    REQUIRE(l.numIterations() == 5);
  }
  SECTION("Long one, many iterations, negative numbers.") {
    w = std::vector<kmeans::Weight>(5, 1);
    d = {{-5},
         {-15},
         {22},
         {27},
         {30}};
    c = {{22},
         {22}};

    centreResults = {{11.8},
                     {0}};
    auto dist = l.runLloydIteration(d, w, c);
    REQUIRE(c == centreResults);
    REQUIRE(dist == 2187);
    REQUIRE(l.numIterations() == 1);

    double k = (79.0 / 3);
    centreResults = {{k},
                     {-10}};

    dist = l.runLloydIteration(d, w, c);
    std::cout<<c[0][0]<<"YESSSW\n";
    REQUIRE(c == centreResults);
    REQUIRE(fabs(dist - 916.32) < 1e-4);
    REQUIRE(l.numIterations() == 2);
    k = (79.0 / 3);
    centreResults = {{k},
                     {-10}};
    dist = l.runLloydIteration(d, w, c);
    REQUIRE(c == centreResults);
    REQUIRE(fabs(dist - 82.667) < 1e-3);
    REQUIRE(l.numIterations() == 3);

    dist = l.runLloydIteration(d, w, c);
    REQUIRE(c == centreResults);
    REQUIRE(fabs(dist - 82.667) < 1e-3);
    REQUIRE(l.numIterations() == 4);
  }
}

TEST_CASE("Simple 1-d case works for runIterations") {
  kmeans::LloydIterationRunner l;

  kmeans::Dataset d;
  kmeans::Weights w;
  kmeans::Dataset c;

  kmeans::Dataset centreResults;
  SECTION("Same dataset and centres works") {
    w = std::vector<kmeans::Weight>(4, 1);
    d = {{1},
         {2},
         {3},
         {4}};
    c = {{1},
         {2},
         {3},
         {4}};
    centreResults = {{1},
                     {2},
                     {3},
                     {4}};
    auto dist = l.runIterations(d, w, c);
    REQUIRE(c == centreResults);
    REQUIRE(l.numIterations() == 2);
    REQUIRE(dist == 0);
  }
  SECTION("Dataset inputted with correct centres works.") {
    w = std::vector<kmeans::Weight>(4, 1);
    d = {{-2},
         {-1},
         {20},
         {25}};
    c = {{-1.5},
         {22.5}};
    centreResults = {{-1.5},
                     {22.5}};
    l.runIterations(d, w, c);
    REQUIRE(c == centreResults);
    REQUIRE(l.numIterations() == 2);
  }
}
