//
// Created by Yaser Alkayale on 2017-07-21.
//

#include <iostream>
#include "../experiments/experiments_bipartite_perfect_matching.h"


int main() {

  //data::BipartiteGraph<double> graph({{12, 11, 14},
  //                                    {10, 4,  12},
  //                                    {9,  11, 13}}, [](double i)->bool { return i >= 0; });
  //graph.breadthFirstSearch([]()->bool { false; });

  auto i = minimumWeightPerfectMatching({{0,1,2},{1,0,2},{1,2,0}});
  for(auto k:i){
    std::cout<<k.first<<", "<<k.second<<std::endl;
  }
  return 0;
}