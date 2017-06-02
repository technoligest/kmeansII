//
// Created by Yaser Alkayale on 2017-05-30.
//

#ifndef KMEANSII_CLUSTER_H
#define KMEANSII_CLUSTER_H

#include "functions.h"
struct cluster{
    Table _values;
    vector<float> _center;
    unsigned long _sum_squared_distances;
    cluster(Table val, vector<float> center):_values(val),_center(center),_sum_squared_distances(0){};
};

#endif //KMEANSII_CLUSTER_H
