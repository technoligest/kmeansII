//
// Created by Yaser Alkayale on 2017-06-01.
//

#ifndef KMEANSII_KMEANSPP_H
#define KMEANSII_KMEANSPP_H


#include "Kmeans.h"

class Kmeanspp : public Kmeans {
public:
    Kmeanspp();

    ~Kmeanspp();

    double cluster(Dataset &d, std::vector<Instance> &centres, ull k) override;




};


#endif //KMEANSII_KMEANSPP_H
