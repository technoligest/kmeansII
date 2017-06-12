//
// Created by Yaser Alkayale on 2017-05-29.
//

#include "Kmeans.h"
#include <math.h>

Kmeans::Kmeans(Table data, const int k) : _table(data), _k(k), _prevDistance(0), _currDistance(0),
                                           _numIterations(0), _sum_squared_distance(0) {}

Kmeans::~Kmeans() {
}

void Kmeans::run() {
    Kmeans::findCentres();
//    runLioydIterations();
//    runIteration();
}


void Kmeans::findCentres() {
    findRandomCentres();
}

//randomly assign centres to the clusters in result
void Kmeans::findRandomCentres() {
    if (_table.empty() || _k < 1) {
        return;
    }
    srand((unsigned) time(NULL)); //this is not the best way to randomize numbers
    size_t size = _table.size();
    for (int i = 0; i < _k; ++i) {
        _result.push_back(Cluster(*_table[rand() % size]));
    }

}

void Kmeans::runLioydIterations() {
    _currDistance = 0;
    _prevDistance = 0;
    do {
        runIteration();
    } while (!stable());
}

void Kmeans::runIteration() {
    std::cout<<"Started iteration"<<std::endl;
    //if we have no cluster centres, then we can't run the iterations.
    if (_result.size() == 0) {
        return;
    }

    clearClusterData();
    ++_numIterations;
    _prevDistance = _currDistance;
    _currDistance = 0;

    for (Row *row: _table.data) {
        float lowest_distance = findDistance(_result[0].centre, *row);
        int temp_i = 0;
        for (int i = 1; i < _result.size(); ++i) {
            float new_distance = findDistance(_result[i].centre, *row);
            if (new_distance < lowest_distance) {
                lowest_distance = new_distance;
                temp_i = i;
            }
        }
        _currDistance += lowest_distance;

        //add the row in the right cluster.
        _result[temp_i].values.add(row);
    }
    calcNewCentres();
    std::cout<<"finished the iteration."<<std::endl;
}


//euclidean distance
float Kmeans::findDistance(Row &r1, Row &r2) {
    return sqrt(findDistanceSquared(r1, r2));
}

//squared euclidean distance
float Kmeans::findDistanceSquared(Row &r1, Row &r2) {
    if (r1.size() != r2.size())
        return 0;
    float result = 0;
    size_t size = r1.size();
    for (int i = 0; i < size; ++i) {
        result += pow(r1[i] - r2[i], 2);
    }
    return result;
}

//calculates the centres for each of the clusters in the result.
void Kmeans::calcNewCentres() {
    std::cout<<"calculating centres"<<std::endl;
    _sum_squared_distance = 0;
    for (auto i: _result) {
        calCentre(i);
        _sum_squared_distance += i.sum_squared_distances;
    }
    std::cout<<"finshed calculating centres"<<std::endl;
}

//calculates the center for the given cluster by finding the mean of each column
//also calculates the sum of squared distances
void Kmeans::calCentre(Cluster &c) {
    c.resetCentre();
    Table t = c.values;
    if (t.empty()) {
        return;
    }
    for (Row *row : t.data) {
        for (int i = 0; i < row->size(); ++i) {
            c.centre[i] = c.centre[i] + (*row)[i] / t.size();
        }
    }
    
    //calculating the distances to each cluster
    c.sum_squared_distances = 0;
    for (auto i: c.values.data) {
        c.sum_squared_distances += findDistance(*i, c.centre);
    }
}

//this empties the values of all the clusters in the result, leaving the centres intact.
void Kmeans::clearClusterData() {
    for (Cluster cluster: _result) {
        cluster.values.clear();
    }
}

//this checks if the current sum of distances is equal to the previous sum of distances
bool Kmeans::stable() {
    return _currDistance == _prevDistance;
}


//returns the result to the user.
std::vector<Cluster> *Kmeans::getResult() {
    return &_result;
}

//returns the number of interations the algorithm took
unsigned long Kmeans::numIterations() const {
    return _numIterations;
}

float Kmeans::sum_squared_distance() const {
    return _sum_squared_distance;
}





