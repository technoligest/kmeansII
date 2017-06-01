//
// Created by Yaser Alkayale on 2017-05-29.
//

#include "Kmeans.h"

Kmeans::Kmeans(const Table &data, const int k) : _data(data), _k(k), _prevDistance(0), _currDistance(0),
                                                 _numIterations(0) {}


void Kmeans::run() {
    findCentres();
    do {
        runItration();
    } while (!stable());
}


//randomly assign centres to stat the algorithm
void Kmeans::findCentres() {
    unsigned long size = _data.size();
    srand((unsigned) time(NULL));
    std::cout << endl;
    for (int i = 0; i < _k; ++i) {
        auto k = _data[rand() % size];
        std::cout <<"The centres: "<< i + 1 << ")\t";
        print(k);
        std::cout << "\n";
        _result.push_back(cluster(Table(), k));
    }
}


void Kmeans::runItration() {
    ++_numIterations;
    cout << "\n\nIteration " << _numIterations << ":"<<endl;
    for (int i=0; i<_result.size(); ++i) {
        cout << "cluster "<<i<<" center: ";
        print(_result[i]._center);
        cout<<endl;
    }

    clearClusters();
    _prevDistance = _currDistance;
    _currDistance = 0;

    for (auto row: _data) {
        float lowest_distance = findDistance(_result[0]._center, row);
        int temp_i = 0;
        cout << "Num of clusters: " << _result.size() << endl;
        for (int i = 1; i < _result.size(); ++i) {
            float new_distance = findDistance(_result[i]._center, row);
            if (new_distance < lowest_distance) {
                lowest_distance = new_distance;
                temp_i = i;
            }
        }
        cout << "adding: ";
        print(row);
        cout << " To cluster " << temp_i << endl;
        _currDistance += lowest_distance;

        //add the row back in the right cluster.
        _result[temp_i]._values.push_back(row);
    }
    calcNewCentres();
}

float Kmeans::findDistance(vector<float> item_1, vector<float> item_2) {
    if (item_1.size() != item_2.size())
        return 0;
    float result = 0;
    size_t size = item_1.size();
    for (int i = 0; i < size; ++i) {
        result += pow(item_1[i] - item_2[i], 2);
    }
    return sqrt(result);
}


//calculates the centres for each of the clusters in the result.
void Kmeans::calcNewCentres() {
    for (int i = 0; i < _result.size(); ++i) {
        calCenter(_result[i]);
    }
}

//calculates the center for the given cluster by finding the mean of each column
void Kmeans::calCenter(cluster &c) {
    Table t = c._values;
    if (t.size() < 1) {
        cout << "cluster is empty!";
        for (auto i = c._center.begin(); i != c._center.end(); ++i) {
            *i = 0;
        }
        return;
    }
    vector<float> temp(t[0].size());

    for (auto row:t) {
        for (int i = 0; i < row.size(); ++i) {
            temp[i] += row[i];
        }
    }
    int size = t.size();
    for (int i = 0; i < temp.size(); ++i) {
        temp[i] = temp[i] / size;
    }
    c._center = temp;
}

//this emties the values of all the clusters in the result.
void Kmeans::clearClusters() {
    for (int i = 0; i < _result.size(); ++i) {
        _result[i]._values.clear();
    }
}

//this checks if the current sum of distances is equal to the previous sum of distances
bool Kmeans::stable() {
    return _currDistance == _prevDistance;
}


//returns the result to the user.
std::vector<cluster> Kmeans::getResult() {
    return _result;
}

//returns the number of interations the algorithm took
unsigned long Kmeans::numIterations() const {
    return _numIterations;
}




