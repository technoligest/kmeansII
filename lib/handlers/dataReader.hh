//
// Created by Yaser Alkayale on 2017-05-29.
//

#ifndef KMEANSII_DATAREADER_H
#define KMEANSII_DATAREADER_H


#include <cmath>
#include <sstream>
#include <fstream>
#include "CSV.hh"
#include "data.hh"
#include "inputArguments.hh"
#include "../pkgs/cmdArgsReader/macro-argparse-plain.hh"
#include "../Algorithm/Kmeans.hh"
#include "../Experiments/experiments.hh"

inline Dataset readCSVFile(std::istream inputFile) {
  Dataset t;
  for (CSVIterator it(inputFile); it != CSVIterator(); ++it) {
    t.push_back(it->toFloat());
  }
  return t;
};

inline Dataset readFile(std::istream inputFile) {
  Dataset result;

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

inline ExperimentResult readExperiment(std::istream istream){

}

inline vector<ExperimentResult> readExperiments(std::istream inputFile){
  std::string tempLine;
  vector<ExperimentResult> result;
  while(getline(inputFile, tempLine)){
    if(tempLine.substr(0,3)==">>>"){
      
      if(readExperiment(inputFile)){

        result.push_back();
      }
    }
  }
}

template<class IR = LloydsIteration>
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
