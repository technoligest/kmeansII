//
// Created by Yaser Alkayale on 2017-05-29.
//

#ifndef KMEANSII_DATAREADER_H
#define KMEANSII_DATAREADER_H


#include <cmath>
#include <sstream>
#include <fstream>
#include "csv.h"
#include "input_arguments.h"
#include "../pkgs/cmdArgsReader/macro-argparse-plain.hh"
#include "../algorithm/kmeans.h"

namespace kmeans{
inline Dataset readCSVDataset(std::istream &inputFile) {
  Dataset t;
  for(CSVIterator it(inputFile); it != CSVIterator(); ++it) {
    t.push_back(it->toDouble());
  }
  return t;
};

inline Dataset readDataset(std::istream &inputFile) {
  Dataset result;

  std::string tempLine;
  //gets each line
  while(getline(inputFile, tempLine)) {
    std::stringstream ss(tempLine);
    std::string tempString;
    Instance i;

    //gets each word in the line
    while(getline(ss, tempString, ' ')) {
      try { i.push_back(stod(tempString)); }
      catch(std::invalid_argument arg) {
        std::cout << "Dataset is corrupt with not all numerical values. TempString: " << tempString << std::endl;
      }
    }
    result.push_back(i);
  }
  return result;
}


template<class IR = LloydIterationRunner>
KmeansBase *readArgs(KmeansArgs args) {
  if(args.algorithm == "kmeans") {
    return new KmeansInstance<RandomSeedPicker, IR>();
  } else if(args.algorithm == "kmeans++") {
    return new KmeansInstance<KmeansppSeedPicker, IR>();
  } else if(args.algorithm == "kmeansII") {
    return new KmeansII<IR, IR>(fabs(args.l));
  } else {
    return NULL;
  }
}

}// namespace kmeans

#endif //KMEANSII_DATAREADER_H
