//
// Created by Yaser Alkayale on 2017-06-04.
//



#ifndef KMEANSII_DATA_H
#define KMEANSII_DATA_H

#include <vector>
#include <iostream>

#define MAX_NUM_ITERATIONS 200
#define LOCAL_ITERATION_BIAS 1.5f
#define CONVERGENCE_THREASHOLD 1

typedef double dataType;
typedef std::string label;

typedef std::vector<dataType> Instance;
typedef std::vector<Instance> Dataset;
typedef std::vector<Instance *> DatasetRefs;

typedef unsigned long long ull;
typedef long long ll;

typedef unsigned int weight;
typedef std::vector<weight> Weights;

typedef double dist;


using namespace std;
inline std::ostream &operator<<(std::ostream &outStream, const Instance &i) {
  if(i.empty()){
    return outStream;
  }
  for(int k = 0; k < i.size() - 1; ++k){
    outStream << i[k] << " ";
  }
  outStream << i[i.size() - 1];
  return outStream;
}

inline std::ostream &operator<<(std::ostream &outStream, const Dataset &d) {
  if(d.empty()){
    return outStream;
  }
  for(int k = 0; k < d.size() - 1; ++k){
    outStream << d[k] << endl;
  }
  outStream << d[d.size() - 1];
  return outStream;
}

#endif //KMEANSII_DATA_H