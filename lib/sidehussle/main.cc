//
// Created by Yaser Alkayale on 2017-07-21.
//

#include "graph.h"


int main() {

  data::BipartiteGraph<double> graph({{12, 11, 14},
                                      {10, 4,  12},
                                      {9,  11, 13}}, [](double i)->bool { return i >= 0; });
  graph.breadthFirstSearch([]()->bool { false; });
  return 0;
}