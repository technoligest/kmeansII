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

  virtual double cluster(Dataset &d, std::vector<Instance> &centres, ull k);


};

namespace KmeansSolver{
 bool analyzeDataset(Dataset &d);
 bool setRandomCentres(Dataset &d, std::vector<Instance> &centres);
 double findDistanceSquared(const Instance &r1, const Instance &r2);
 double runLiyodIteration(Dataset &d, std::vector<Instance> &centres);
 double runLiyodIterations(Dataset &d, std::vector<Instance> &centres);
 bool prepareForClustering(Dataset &d, std::vector<Instance> &centres, ull k);
}

#endif //KMEANSII_KMEANS_H

