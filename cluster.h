//
// Created by Yaser Alkayale on 2017-05-30.
//

#ifndef KMEANSII_CLUSTER_H
#define KMEANSII_CLUSTER_H

#include "functions.h"
struct cluster{
    Table _values;
    vector<float> _center;
    cluster(Table val, vector<float> center):_values(val),_center(center){};
};

#endif //KMEANSII_CLUSTER_H
