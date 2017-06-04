//
// Created by Yaser Alkayale on 2017-05-30.
//

#ifndef KMEANSII_FUNCTIONS_H
#define KMEANSII_FUNCTIONS_H

#include <string>
#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

template <typename T>
inline void print(vector<T> arr){
    for(T i: arr){
        std::cout<<i<<"\t";
    }
}

#endif //KMEANSII_FUNCTIONS_H
