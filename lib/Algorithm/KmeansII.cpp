//
// Created by Yaser Alkayale on 2017-06-04.
//

#include "KmeansII.h"

KmeansII::KmeansII(Table &_data, const int k, const double l) : Kmeanspp(_data, k), _l(l) {}
KmeansII::~KmeansII(){}

void KmeansII::findCentres() {
    if (_table.empty() || _k < 1) {
        return;
    }
    size_t size = _table.size();
    srand((unsigned) time(NULL));
    _result.push_back(Cluster(*_table[rand() % size]));
    int passes = (int)calcDX(_table, _result);
    for (int i = 0; i < passes; ++i) {
        float dx = Kmeanspp::calcDX(_table,_result);
        float ran = (float) rand() / RAND_MAX;
        for (auto row: _table.data) {
            float probability = _l*Kmeanspp::shortestDistanceToClusterCentre(_result,*row) / dx;
            if (ran <= probability) {
                _result.push_back(Cluster(*row));
            }
        }
    }
}

void KmeansII::run() {
    KmeansII::findCentres();
    Table temp;
    for(Cluster c: _result){
        temp.add(&c.centre);
    }
    Kmeanspp kmeans(temp,_k);
    kmeans.run();
    auto result = kmeans.getResult();
    _result.clear();
    for(auto i:*result){
        _result.push_back(Cluster(i.centre));
    }
    Kmeans::runLioydIterations();
}

