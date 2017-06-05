//
// Created by Yaser Alkayale on 2017-06-04.
//

#include "KmeansII.h"

KmeansII::KmeansII(const Table &_data, const int k, const double l) : Kmeans(_data, k), _l(l) {}

double KmeansII::findCost(const Table &data, const vector<float>* row){

}

double KmeansII::findMinDistance(const Table &data, const vector<float>* row){

}

void KmeansII::run() {
    srand((unsigned) time(NULL));
    auto row = _data[rand() % _data.size()];
    double cost = findCost(_data,row );

}

