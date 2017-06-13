//
// Created by Yaser Alkayale on 2017-06-01.
//

#include "Kmeanspp.h"

Kmeanspp::Kmeanspp(Table &_data, const int k) : Kmeans(_data, k) {}
Kmeanspp::~Kmeanspp(){};
void Kmeanspp::run() {
    Kmeanspp::findCentres();
    Kmeans::runLioydIterations();
}

void Kmeanspp::findCentres() {
    if ( _table.empty() || _k < 1) {
        return;
    }
    size_t size = _table.size();
    srand((unsigned) time(NULL));

    _result.push_back(Cluster(*_table[rand() % size]));

    for (int i = 1; i < _k; ++i) {
        double dx = calcDX(_table,_result);
        double ran = (double) rand() / RAND_MAX;

        double tem = 0;
        for (auto row: _table.data) {
            double distance = shortestDistanceToClusterCentre(_result,*row) / dx;
            tem += distance;
            if (ran <= tem) {
                _result.push_back(Cluster(*row));
                break;
            }
        }
    }
}

//DX is the sum of the shortest paths from each item to the nearest cluster.
double Kmeanspp::calcDX(const Table &t, const std::vector<Cluster> &clusters) {
    if (clusters.size() < 1) {
        return -1;
    }
    double result = 0;
    for (auto row: t.data) {
        result += shortestDistanceToClusterCentre(clusters, *row);
    }
    return result;
}

//find the shortest distance to any already chosen cluster for the given row.
double Kmeanspp::shortestDistanceToClusterCentre(const std::vector<Cluster> &clusters, Row &row) {
    if (_result.empty())
        return -1;
    double currDistance,lowestDistance;
    lowestDistance = currDistance = findDistance(row, _result[0].centre);

    for (Cluster cluster: _result) {
        currDistance = findDistance(row, cluster.centre);
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


