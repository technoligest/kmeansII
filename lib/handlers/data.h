//
// Created by Yaser Alkayale on 2017-06-04.
//



#ifndef KMEANSII_DATA_H
#define KMEANSII_DATA_H

#include <vector>
#include <iostream>

#define MAX_NUM_ITERATIONS 200
#define LOCAL_ITERATION_BIAS 1.5f

typedef double dataType;
typedef std::string label;

typedef std::vector<dataType> Instance;
typedef std::vector<Instance> Dataset;
typedef std::vector<Instance *> DatasetRefs;

typedef unsigned long long ull;
typedef long long ll;

#endif //KMEANSII_DATA_H