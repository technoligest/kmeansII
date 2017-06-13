//
// Created by Yaser Alkayale on 2017-05-29.
//

#ifndef KMEANSII_KMEANS_H
#define KMEANSII_KMEANS_H

#include "../handlers/data.h"


class Kmeans {
public:
    Kmeans();

    ~Kmeans();

    virtual void run();

    virtual std::vector<Cluster> *getResult();

    virtual unsigned long numIterations() const;

    virtual double sum_squared_distance() const;

    virtual double cluster(Dataset &d, std::vector<Instance> &centres, ull k);

protected:
    ull _numIterations;
    double _sum_squared_distance;

    void runLioydIterations(); //runs Lyod's iterations
    void runIteration();  //runs one iteration
    double findDistance(Row &, Row &);

    double findDistanceSquared(Row &, Row &);

    void calcNewCentres();

    void calCentre(Cluster &);

    void clearClusterData();

    virtual void findCentres();

private:
    bool stable();

    double _prevDistance;
    double _currDistance;

    void findRandomCentres();
};


#endif //KMEANSII_KMEANS_H

