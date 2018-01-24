//
// Created by Yaser Alkayale on 2017-07-04.
//

#ifndef KMEANSII_EXPERIMENTSREADER_HH
#define KMEANSII_EXPERIMENTSREADER_HH


#include "experiment_result.h"

namespace kmeans{
namespace experiments{
namespace reader{

Dataset readCentres(std::istream &file);
ExperimentResult readExperimentBody(std::istream &file);
std::vector<ExperimentResult> readExperiments(std::istream &file);
bool printExperiments(const std::string &dataSetName, const std::vector<ExperimentResult> experiments, const std::string& dir);

} //namespace reader
} //namespace experiments
} //namespace kmeans

#endif //KMEANSII_EXPERIMENTSREADER_HH
