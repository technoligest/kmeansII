//
// Created by Yaser Alkayale on 2017-06-04.
//

#ifndef KMEANSII_KMEANSII_H
#define KMEANSII_KMEANSII_H


#include "Kmeans.h"
#include "Kmeanspp.h"

class KmeansII : public KmeansBase {
public:
  KmeansII(double);

  ~KmeansII();

  double cluster(Dataset &, std::vector<Instance> &, ull);

  double cluster(Dataset &, std::vector<Instance> &, Weights, ull);

private:
  double l;
};

namespace KmeansIISolver {
 void findCentres(Dataset &, std::vector<Instance> &, ull, double);
}
#endif //KMEANSII_KMEANSII_H
