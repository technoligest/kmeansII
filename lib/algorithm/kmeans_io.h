//
// Created by Yaser Alkayale on 2017-05-29.
//

#ifndef KMEANSII_DATAREADER_H
#define KMEANSII_DATAREADER_H


#include <cmath>
#include <sstream>
#include <fstream>
#include "csv.h"
#include "kmeans_input_arguments.h"
#include "kmeans.h"
#include "globals.h"

namespace kmeans{
/*
 * Every instance has to be on a single line
 */
Dataset readCSVDataset(std::istream &inputFile);
Dataset readDataset(std::istream &inputFile);

std::ostream &operator<<(std::ostream &, const Weights &);
std::ostream &operator<<(std::ostream &, const Instance &);
std::ostream &operator<<(std::ostream &, const Dataset &);
}// namespace kmeans

#endif //KMEANSII_DATAREADER_H
