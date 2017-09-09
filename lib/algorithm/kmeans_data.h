//
// Created by Yaser Alkayale on 2017-06-04.
//



#ifndef KMEANSII_DATA_H
#define KMEANSII_DATA_H

#include <vector>
#include <iostream>

typedef unsigned long long ull;
typedef long long ll;

namespace kmeans{

#define MAX_NUM_ITERATIONS 200
#define LOCAL_ITERATION_BIAS 1.5f
#define CONVERGENCE_THREASHOLD 1
template<typename T>
using Matrix = std::vector<std::vector<T>>;

typedef std::vector<int>::size_type Index;
typedef double DataType;
typedef std::string label; //A label for a given value in the dataset_

typedef std::vector<DataType> Instance;
typedef std::vector<Instance> Dataset;
typedef std::vector<ull> DatasetIds;
typedef std::vector<Instance *> DatasetRefs;


typedef unsigned int Weight;
typedef std::vector<Weight> Weights;

typedef double Distance;

bool operator==(const Instance &instance1,const Instance &instance2);

//not sure if I should add the other operators as well.
void operator/=(Instance &, const std::vector<size_t> &);



void operator+=(Instance &, const Instance &);
void operator-=(Instance &, const Instance &);
void operator*=(Instance &, const Instance &);
void operator/=(Instance &, const Instance &);

} //namespace kmeans

#endif //KMEANSII_DATA_H