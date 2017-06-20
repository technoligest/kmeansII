//
// Created by Yaser Alkayale on 2017-05-29.
//

#ifndef KMEANSII_DATAREADER_H
#define KMEANSII_DATAREADER_H


#include <cmath>
#include <sstream>
#include <fstream>
#include "CSV.h"
#include "data.h"
#include "inputArguments.hh"
#include "../pkgs/cmdArgsReader/macro-argparse-plain.hh"
#include "../Algorithm/Kmeans.h"
#include "../Algorithm/IterationRunners.h"

inline Dataset readCSVFile(const std::string &fileName) {
  Dataset t;
  std::ifstream inputFile(fileName);
  for (CSVIterator it(inputFile); it != CSVIterator(); ++it) {
    t.push_back(it->toFloat());
  }
  return t;
};

inline Dataset readFile(const std::string &fileName) {
  Dataset result;
  std::ifstream inputFile(fileName);

  if (!inputFile.is_open()) {
    return result;
  }

  std::string tempLine;
  //gets each line
  while (getline(inputFile, tempLine)) {
    std::stringstream ss(tempLine);
    std::string tempString;
    Instance i;
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

template<class IR = LiyoidsIteration>
KmeansBase *readArgs(KmeansArgs args) {
  if (args.algorithm == "kmeans") {
    return new KmeansInitializer<RandomSeedPicker,IR>();
  } else if (args.algorithm == "kmeans++") {
    return new KmeansInitializer<KmeansppSeedPicker,IR>();
//  } else if (args.algorithm == "kmeansII") {
//    return new KmeansII(fabs(args.l));
  } else {
    return NULL;
  }
}

#endif //KMEANSII_DATAREADER_H
