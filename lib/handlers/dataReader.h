//
// Created by Yaser Alkayale on 2017-05-29.
//

#ifndef KMEANSII_DATAREADER_H
#define KMEANSII_DATAREADER_H


#include <cmath>
#include "CSV.h"
#include "data.h"
#include "inputArguments.hh"
#include "../pkgs/macro-argparse-plain.hh"
#include "../Algorithm/Kmeans.h"
#include "../Algorithm/Kmeanspp.h"
#include "../Algorithm/KmeansII.h"

inline Dataset readFile(std::string fileName) {
  Dataset t;
  std::ifstream inputFile(fileName);
  for (CSVIterator it(inputFile); it != CSVIterator(); ++it) {
    t.push_back(it->toFloat());
  }
  return t;
};


Kmeans *readArgs(KmeansArgs args) {
  if (args.algorithm == "kmeans") {
    return new Kmeans();
  } else if (args.algorithm == "kmeans++") {
    return new Kmeanspp();
  } else if (args.algorithm == "kmeansII") {
    return new KmeansII(fabs(args.l));
  }
  else {
    return NULL;
  }
}

#endif //KMEANSII_DATAREADER_H
