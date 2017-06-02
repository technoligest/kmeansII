//
// Created by Yaser Alkayale on 2017-06-01.
//

#include "Kmeanspp.h"

Kmeanspp::Kmeanspp(const Table &_data, const int k) : Kmeans(_data, k) {}

void Kmeanspp::run() {
    Kmeanspp::findCentres();
    do {
        Kmeans::runItration();
    } while (!stable());
}

void Kmeanspp::findCentres() {
    if (_data.size() < 1 || _k < 1) {
        return;
    }
    size_t size = _data.size();
    srand((unsigned) time(NULL));
    auto k = _data[rand() % size];
    _result.push_back(cluster(Table(), k));

    for (int i = 1; i < _k; ++i) {
        float dx = calcDX();
        float ran = (float) rand() / RAND_MAX;

        float tem = 0;
        for (auto row: _data) {
            float distance = shortestDistanceToClusterCenter(row) / dx;
            tem += distance;
            if (ran <= tem) {
                _result.push_back(cluster(Table(), row));
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
    for (auto row: _data) {
        result += shortestDistanceToClusterCenter(row);
    }
    return result;
}

float Kmeanspp::shortestDistanceToClusterCenter(vector<float> row) {
    if (_result.size() < 1)
        return -1;
    float currDistance = findDistance(row, _result[0]._center);
    float lowestDistance = currDistance;
    for (int i = 1; i < _result.size(); ++i) {
        float currDistance = findDistance(row, _result[i]._center);
        if (currDistance < lowestDistance) {
            lowestDistance = currDistance;
        }
    }
    return lowestDistance;
}

vector<cluster, allocator<cluster>> Kmeanspp::getResult() {
    return Kmeans::getResult();
}

unsigned long Kmeanspp::numIterations() const {
    return Kmeans::numIterations();
}


