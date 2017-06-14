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

namespace KmeansSolver {
 bool analyzeDataset(Dataset &d);

 bool setRandomCentres(Dataset &, std::vector<Instance> &);

 double findDistanceSquared(const Instance &, const Instance &);

 double runLiyodIteration(Dataset &, std::vector<Instance> &);

 double runLiyodIterations(Dataset &, std::vector<Instance> &);

 bool prepareForClustering(Dataset &, std::vector<Instance> &, ull);
}

#endif //KMEANSII_KMEANS_H

