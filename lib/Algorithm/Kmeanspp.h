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

namespace KmeansppSolver{
 double shortestDistanceToClusterCentre(const std::vector<Instance> &, const Instance &);
 double calcDX(const Dataset &, const std::vector<Instance> &);
 void findCentres(Dataset &, std::vector<Instance> &, ull);

}


#endif //KMEANSII_KMEANSPP_H
