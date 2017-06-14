//
// Created by Yaser Alkayale on 2017-06-04.
//

#ifndef KMEANSII_KMEANSII_H
#define KMEANSII_KMEANSII_H


#include "Kmeans.h"
#include "Kmeanspp.h"

class KmeansII : public Kmeans {
public:
  KmeansII(double);

  ~KmeansII();

  double cluster(Dataset &d, std::vector<Instance> &centres, ull k);

private:
  double l;
};

namespace KmeansIISolver{
 void findCentres(Dataset &, std::vector<Instance> &, ull,ll);
}
#endif //KMEANSII_KMEANSII_H
