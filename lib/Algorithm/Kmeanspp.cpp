//
// Created by Yaser Alkayale on 2017-06-01.
//

#include "Kmeanspp.h"

Kmeanspp::Kmeanspp(const Table &_data, const int k) : Kmeans(_data, k) {}

void Kmeanspp::run() {
    Kmeanspp::findCentres();
    Kmeans::runIterations();
}

void Kmeanspp::findCentres() {
    if (_table.data->size() < 1 || _k < 1) {
        return;
    }
    size_t size = _table.data->size();
    srand((unsigned) time(NULL));
    auto k = (*_table.data)[rand() % size];
    _result.push_back(Cluster(Table(), k));

    for (int i = 1; i < _k; ++i) {
        float dx = calcDX();
        float ran = (float) rand() / RAND_MAX;

        float tem = 0;
        for (auto row: *_table.data) {
            float distance = shortestDistanceToClusterCenter(*row) / dx;
            tem += distance;
            if (ran <= tem) {
                _result.push_back(Cluster(Table(), row));
                break;
            }
        }
    }
}

//DX is the sum of the shortest paths from each item to the nearest cluster.
float Kmeanspp::calcDX() {
    if (_result.size() < 1) {
        return -1;
    }
    float result = 0;
    for (auto row: *_table.data) {
        result += shortestDistanceToClusterCenter(*row);
    }
    return result;
}


//find the shortest distance to any already chosen cluster.
float Kmeanspp::shortestDistanceToClusterCenter(const Row &row) {
    if (_result.empty())
        return -1;
    float currDistance,lowestDistance;

    lowestDistance = currDistance = findDistance(row, *_result[0]._center);

    for (Cluster cluster: _result) {
        float currDistance = findDistance(row, *cluster._center);
        if (currDistance < lowestDistance) {
            lowestDistance = currDistance;
        }
    }
    return lowestDistance;
}

std::vector<Cluster>* Kmeanspp::getResult() {
    return Kmeans::getResult();
}

unsigned long Kmeanspp::numIterations() const {
    return Kmeans::numIterations();
}


