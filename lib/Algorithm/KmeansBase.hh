//
// Created by Yaser Alkayale on 2017-06-19.
//

#ifndef KMEANSII_KMEANSBASE_H
#define KMEANSII_KMEANSBASE_H


#include "../handlers/data.hh"

class KmeansBase {
public:
  virtual dist cluster(const Dataset &, Dataset &, ull)=0;

  virtual dist cluster(const Dataset &, Dataset &, const Weights &, ull)=0;
};


#endif //KMEANSII_KMEANSBASE_H
