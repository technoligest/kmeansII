//
// Created by Yaser Alkayale on 2017-05-29.
//

#ifndef KMEANSII_KMEANS_H
#define KMEANSII_KMEANS_H

#include "../handlers/data.h"


class Kmeans {
public:
    Kmeans(Table _data, const int k);

    ~Kmeans();

    virtual void run();

    virtual std::vector<Cluster> *getResult();

    virtual unsigned long numIterations() const;

    virtual float sum_squared_distance() const;

protected:
    Table _table;
    int _k; //this is the number of centres that we need to have.
    std::vector<Cluster> _result; //These are the final clusters which should be of size _k
    unsigned long long _numIterations;
    float _sum_squared_distance;

    void runLioydIterations(); //runs Lyod's iterations
    void runIteration();  //runs one iteration
    float findDistance(Row &, Row &);

    float findDistanceSquared(Row &, Row &);

    void calcNewCentres();

    void calCentre(Cluster &);

    void clearClusterData();

    virtual void findCentres();

private:
    bool stable();

    float _prevDistance;
    float _currDistance;

    void findRandomCentres();
};


#endif //KMEANSII_KMEANS_H

