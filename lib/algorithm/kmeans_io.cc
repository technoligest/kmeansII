//
// Created by Yaser Alkayale on 2017-08-28.
//


#include "kmeans_io.h"

namespace kmeans{

std::ostream &operator<<(std::ostream &out_stream, const Weights &weights) {
  if(weights.empty()) {
    return out_stream;
  }
  size_t size_less_one = weights.size();
  for(size_t i = 0; i < size_less_one; ++i) {
    out_stream << weights[i] << " ";
  }
  out_stream << weights[size_less_one];
  return out_stream;
}

std::ostream &operator<<(std::ostream &out_stream, const Instance &instance) {
  if(instance.empty()) {
    return out_stream;
  }
  size_t size_less_one = instance.size()-1;
  for(size_t i = 0; i < size_less_one; ++i) {
    out_stream <<instance[i] << ",";
  }
  out_stream << instance[size_less_one];
  return out_stream;
}

std::ostream &operator<<(std::ostream &out_stream, const Dataset &dataset) {
  if(dataset.empty()) {
    return out_stream;
  }
  for(int i = 0; i < dataset.size() - 1; ++i) {
    out_stream << dataset[i] << std::endl;
  }
  out_stream << dataset[dataset.size() - 1];
  return out_stream;
}

Dataset readCSVDataset(std::istream &inputFile) {
  Dataset t;
  for(CSVIterator it(inputFile); it != CSVIterator(); ++it) {
    t.push_back(it->toDouble());
  }
  return t;
}

Dataset readDataset(std::istream &inputFile) {
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
}//namespace kmeans