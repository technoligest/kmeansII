//
// Created by Yaser Alkayale on 2017-06-01.
//

#ifndef KMEANSII_KMEANSPP_H
#define KMEANSII_KMEANSPP_H


#include "Kmeans.h"

class Kmeanspp : Kmeans {
public:
    Kmeanspp(const Table &_data, const int k);

    void run() override;

    vector<Cluster>* getResult() override;

    unsigned long numIterations() const override;

private:


    void findCentres() override;

    float shortestDistanceToClusterCenter(const Row &row);

    float calcDX();

    vector<float> pickRowWProb(float);
};


#endif //KMEANSII_KMEANSPP_H
