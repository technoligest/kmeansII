//
// Created by Yaser Alkayale on 2017-05-29.
//

#ifndef KMEANSII_KMEANS_H
#define KMEANSII_KMEANS_H



#include "../handlers/data.h"


class Kmeans {
public:
    Kmeans(const Table &_data, const int k);
    virtual void run();
    virtual std::vector<Cluster>* getResult();
    virtual unsigned long numIterations() const;

protected:
    const Table _table;
    int _k; //this is the number of centres that we need to have.
    std::vector<Cluster> _result; //These are the final clusters which should be of size _k
    unsigned long long _numIterations;

    void runIterations(); //runs Lyod's iterations
    void runIteration();  //runs one iteration
    float findDistance(const Row&, const Row&);
    void calcNewCentres();
    void calCenter(Cluster&);
    void clearClusters();
    virtual void findCentres();

private:
    bool stable();
    float _prevDistance;
    float _currDistance;
    virtual void findRandomCentres();
};


#endif //KMEANSII_KMEANS_H

