//
// Created by Yaser Alkayale on 2017-05-29.
//

#ifndef KMEANSII_KMEANS_H
#define KMEANSII_KMEANS_H


#include <vector>
#include <string>
#include <stdlib.h>
#include <time.h>
#include "functions.h"
#include "cluster.h"


class Kmeans {
public:
    Kmeans(const Table &_data, const int k);

    virtual void run();

    virtual std::vector<cluster> getResult();

    virtual unsigned long numIterations() const;

protected:
    Table _data;
    std::vector<int> _centres; //stores the locations of the centres in the table.
    int _k; //this is the number of centres that we need to have.
    std::vector<cluster> _result; //These are the final cluters which shoud be of size _k
    unsigned long long _prevDistance;
    unsigned long long _currDistance;

    void runItration();

    float findDistance(vector<float>, vector<float>);

    void calcNewCentres();

    void calCenter(cluster&);

    virtual void findCentres();

    void clearClusters();

    bool stable();
    unsigned long _numIterations;


};


#endif //KMEANSII_KMEANS_H

