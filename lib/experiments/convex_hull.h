//
// Created by Yaser Alkayale on 2017-07-19.
//

#ifndef KMEANSII_CONVEX_HULL_H
#define KMEANSII_CONVEX_HULL_H

#include <cassert>
#include <cmath>
#include "../algorithm/kmeans_data.h"
#include "../algorithm/kmeans_helpers.h"

namespace kmeans{
namespace experiments{

Dataset calculateConvexHull(Dataset dataset);

}//namespace experiments
}//namespace kmeans



#endif //KMEANSII_CONVEX_HULL_H
