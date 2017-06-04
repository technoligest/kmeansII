//
// Created by Yaser Alkayale on 2017-05-29.
//

#include "Kmeans.h"
#include <math.h>

Kmeans::Kmeans(const Table &data, const int k) : _table(data), _k(k), _prevDistance(0), _currDistance(0),
                                                 _numIterations(0) {}


void Kmeans::run() {
    findRandomCentres();
    runIterations();
}

//randomly assign centres to stat the algorithm
void Kmeans::findRandomCentres() {
    size_t size = _table.data->size();
    srand((unsigned) time(NULL));
    for (int i = 0; i < _k; ++i) {
        auto k = (*_table.data)[rand() % size];
        _result.push_back(Cluster(Table(), k));
    }
}

void Kmeans::runIteration() {
    ++_numIterations;
    clearClusters();
    _prevDistance = _currDistance;
    _currDistance = 0;

    for (Row *row: *_table.data) {
        float lowest_distance = findDistance(*_result[0]._center, *row);
        int temp_i = 0;
        for (int i = 1; i < _result.size(); ++i) {
            float new_distance = findDistance(*_result[i]._center, *row);
            if (new_distance < lowest_distance) {
                lowest_distance = new_distance;
                temp_i = i;
            }
        }
        _currDistance += lowest_distance;

        //add the row in the right cluster.
        _result[temp_i]._values.data->push_back(row);
    }
    calcNewCentres();
}


//squared euclidean distance
float Kmeans::findDistance(const Row &r1, const Row &r2) {
    if (r1.data->size() != r2.data->size())
        return 0;
    float result = 0;
    size_t size = r1.data->size();
    for (int i = 0; i < size; ++i) {
        result += pow((*r1.data)[i] - (*r2.data)[i], 2);
    }
    return result;
}


//calculates the centres for each of the clusters in the result.
void Kmeans::calcNewCentres() {
    for (auto i: _result) {
        calCenter(i);
    }
}

//calculates the center for the given cluster by finding the mean of each column
//also calculates the sum of squared distances
void Kmeans::calCenter(Cluster &c) {
    if (c._center == NULL)
        return;
    Table t = c._values;
    if (t.data->empty()) {
        for (auto i = c._center->data->begin(); i != c._center->data->end(); ++i) {
            *i = 0;
        }
        return;
    }
    std::vector<float> *temp = new std::vector<float>((*t.data)[0]->data->size());

    for (auto row : *t.data) {
        for (int i = 0; i < row->data->size(); ++i) {
            (*temp)[i] += (*row->data)[i];
        }
    }
    int size = t.data->size();
    for (int i = 0; i < temp->size(); ++i) {
        (*temp)[i] = (*temp)[i] / size;
    }
    c._center = new Row(temp);

    //calculating the distances to each cluster
    float sum_distances = 0;
    for (auto i: *c._values.data) {
        sum_distances = findDistance(*i, *c._center);
    }
    c._sum_squared_distances = sum_distances;
}

//this emties the values of all the clusters in the result.
void Kmeans::clearClusters() {

    for (auto cluster: _result) {
        cluster._values.data->clear();
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

void Kmeans::runIterations() {
    _currDistance = 0;
    _prevDistance = 0;
    do {
        runIteration();
    } while (!stable());
}




