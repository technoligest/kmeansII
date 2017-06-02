//
// Created by Yaser Alkayale on 2017-05-30.
//

#ifndef KMEANSII_FUNCTIONS_H
#define KMEANSII_FUNCTIONS_H

#include <string>
#include <iostream>
#include <vector>
#include <math.h>

using Table = std::vector<std::vector<float>>;
using namespace std;

template <typename T>
inline void print(vector<T> arr){
    for(T i: arr){
        std::cout<<i<<"\t";
    }
}

inline void printTable(Table t){
    for(auto i:t){
        for(auto j: i){
            std::cout<<j<<"\t";
        }
        std::cout<<endl;
    }
}

#endif //KMEANSII_FUNCTIONS_H
