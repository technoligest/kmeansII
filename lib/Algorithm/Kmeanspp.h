//
// Created by Yaser Alkayale on 2017-06-01.
//

#ifndef KMEANSII_KMEANSPP_H
#define KMEANSII_KMEANSPP_H


#include "Kmeans.h"

class Kmeanspp : protected Kmeans {
public:
    Kmeanspp(Table &_data, const int k);

    ~Kmeanspp();

    void run() override;

    std::vector<Cluster> *getResult() override;

    unsigned long numIterations() const override;

protected:
    float shortestDistanceToClusterCentre(const std::vector<Cluster> &, Row &);

    float calcDX(const Table &, const std::vector<Cluster> &);

private:
    void findCentres() override;


};


#endif //KMEANSII_KMEANSPP_H
