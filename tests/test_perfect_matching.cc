//
// Created by Yaser Alkayale on 2017-07-18.
//

#include "catch.hpp"
#include "../lib/experiments/hungarian.h"
#include "../lib/algorithm/kmeans_data.h"

TEST_CASE("Perfect Matching Works") {
  auto infinity = std::numeric_limits<kmeans::Distance>::max();
  kmeans::Matrix<kmeans::Distance> matrix{{0, 0,  0,  0},
                                          {0, 12, 15, 8},
                                          {0, 15, 17, 1},
                                          {0, 8,  3,  11}};
  matrix = {
      {1,2,3},
      {3,1,2},
      {3,2,1}
  };
  auto result = kmeans::experiments::minimumWeightPerfectMatching(matrix);

  //for(const auto &i:result) {
  //  std::cout << std::get<0>(i)<<", "<<std::get<1>(i) << "\t";
  //}

}