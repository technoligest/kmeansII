//
// Created by Yaser Alkayale on 2017-05-29.
//

#ifndef KMEANSII_DATAREADER_H
#define KMEANSII_DATAREADER_H


#include <cmath>
#include <sstream>
#include <fstream>
#include "CSV.hh"
#include "inputArguments.hh"
#include "../pkgs/cmdArgsReader/macro-argparse-plain.hh"
#include "../Algorithm/Kmeans.hh"

inline KmeansData::Dataset readCSVDataset(std::istream &inputFile) {
  KmeansData::Dataset t;
  for (CSVIterator it(inputFile); it != CSVIterator(); ++it) {
    t.push_back(it->toFloat());
  }
  return t;
};

inline KmeansData::Dataset readDataset(std::istream &inputFile) {
  KmeansData::Dataset result;

  std::string tempLine;
  //gets each line
  while (getline(inputFile, tempLine)) {
    std::stringstream ss(tempLine);
    std::string tempString;
    KmeansData::Instance i;

    //gets each word in the line
    while (getline(ss, tempString, ' ')) {
      try {
        i.push_back(stod(tempString));
      }
      catch (std::invalid_argument arg) {
        std::cout << "Dataset is corrupt with not all numerical values";
      }
    }
    result.push_back(i);
  }
  return result;
}


template<class IR = LloydIterationRunner>
KmeansBase *readArgs(KmeansArgs args) {
  if (args.algorithm == "kmeans") {
    return new KmeansInstance<RandomSeedPicker,IR>();
  } else if (args.algorithm == "kmeans++") {
    return new KmeansInstance<KmeansppSeedPicker,IR>();
  } else if (args.algorithm == "kmeansII") {
    return new KmeansII<IR,IR>(fabs(args.l));
  } else {
    return NULL;
  }
}

#endif //KMEANSII_DATAREADER_H
