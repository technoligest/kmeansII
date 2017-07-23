//
// Created by Yaser Alkayale on 2017-07-18.
//

#ifndef KMEANSII_CENTRE_INTERSECTIONS_H
#define KMEANSII_CENTRE_INTERSECTIONS_H

#include "../algorithm/kmeans_data.h"

namespace kmeans{
namespace experiments{

struct CentreIntersectionInstance{
  ull numIntersection;
  ull numCluster1;
  ull numCluster2;
};

struct CentreIntersections{
  CentreIntersections(std::vector<CentreIntersectionInstance> &&insts) : instances(insts) {}

  std::vector<CentreIntersectionInstance> instances;
};

}//namespace experiments
}//namespace kmeans



#endif //KMEANSII_CENTRE_INTERSECTIONS_H
