//
// Created by Yaser Alkayale on 2017-06-04.
//

#ifndef KMEANSII_KMEANSII_H
#define KMEANSII_KMEANSII_H


#include "Kmeans.h"

class KmeansII : Kmeans{
public:
    KmeansII(const Table &_data, const int k, const double l);

private:
    void run() override;

private:
    double _l;
    Table _tempCentres;

    double findCost(const Table &data, const vector<float, allocator<float>> *row);
};


#endif //KMEANSII_KMEANSII_H
