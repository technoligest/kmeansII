//
// Created by Yaser Alkayale on 2017-07-15.
//
#include "experiments_io.h"
#include "experiment_helpers.h"
#include <sstream>
#include <fstream>


namespace kmeans{
namespace experiments{
namespace reader{

/*
 * Given a file, read the points from that file into a dataset
 */
Dataset readCentres(std::istream &file) {
  Dataset result;
  while(file.good()) {
    std::string line;
    std::getline(file, line);
    if(line.substr(0, 3) == "End") {
      return result;
    }
    std::stringstream lineStream(line);
    std::string item;
    Instance i;
    while(std::getline(lineStream, item, ' ')) {
      try {
        double k = stod(item);
        i.push_back(stod(item));
      }
      catch(std::invalid_argument e) {
        std::cout << item << "---Invalid entry in the centres." << std::endl;
      }
    }
    if(!i.empty())
      result.push_back(i);
  }
  result.clear();
  return result;
}

ExperimentResult readExperimentBody(std::istream &file) {
  std::string line;
  ExperimentResult result;
  while(file.good()) {
    std::string delimed;
    getline(file, line, ':');
    if(line == "algorithm") {
      std::getline(file, line);
      result.algorithm = line.substr(1);
    } else if(line == "Sum of distance squared to centre") {
      std::getline(file, line);
      try {
        result.distanceSquared = stod(line.substr(1));
      }
      catch(std::invalid_argument e) {
        std::cout << "Invalid File Input for Distance Squared." << std::endl;
      }
    } else if(line == "Time to pick the seeds") {
      std::getline(file, line);
      try {
        result.seedPickerTime = stoull(line.substr(1));
      }
      catch(std::invalid_argument e) {
        std::cout << "Invalid File Input for Time to pick the seeds." << std::endl;
      }
    } else if(line == "Number of iterations run") {
      std::getline(file, line);
      try {
        result.numIterations = stoull(line.substr(1));
      }
      catch(std::invalid_argument e) {
        std::cout << "Invalid File Input for number of iterations run." << std::endl;
      }
    } else if(line == "Time to run the iterations") {
      std::getline(file, line);
      try {
        result.iterationTime = stoull(line.substr(1));
      }
      catch(std::invalid_argument e) {
        std::cout << "Invalid File Input for time to run iterations." << std::endl;
      }
    } else if(line == "Start Centres") {
      std::getline(file, line);
      result.centres = readCentres(file);
    } else if(line.substr(0, 3) == "End") {
      return result;
    }
  }
  result.distanceSquared = -1;
  result.centres.clear();
  result.iterationTime = -1;
  result.numIterations = 0;
  result.algorithm = "NOTHING";
  result.seedPickerTime = 0;
  return result;
}

std::vector<ExperimentResult> readExperiments(std::istream &file) {
  std::vector<ExperimentResult> result;
  while(file.good()) {
    std::string line;
    std::getline(file, line
    );
    if(line.substr(0, 3) == ">>>") {
      result.push_back(readExperimentBody(file));
    }
  }
  return
      result;
}

bool
printExperiments(const std::string &dataSetName, const std::vector<ExperimentResult> experiments, const std::string &dir) {
  /*
   * Finding the next number to enter for the test
   * Taking the max of the 3 prefixes for each of the algorithms.
   */
  ull num = std::max(helpers::lastNumberedFile(dir, "kmeans-" + dataSetName + "-test"),
                     std::max(helpers::lastNumberedFile(dir, "kmeans++-" + dataSetName + "-test"),
                              helpers::lastNumberedFile(dir, "kmeans||-" + dataSetName + "-test")));


  std::string postFix = "-" + dataSetName + "-test" + std::to_string(num) + ".txt";
  std::ofstream kOutputFile(dir + "/kmeans" + postFix);
  std::ofstream kppOutputFile(dir + "/kmeans++" + postFix);
  std::ofstream k2OutputFile(dir + "/kmeans||" + postFix);
  for(const auto &i: experiments) {
    if(i.algorithm == "Kmeans") {
      kOutputFile << i << std::endl;
    } else if(i.algorithm == "Kmeans++") {
      kppOutputFile << i << std::endl;
    } else if(i.algorithm == "Kmeans||") {
      k2OutputFile << i << std::endl;
    }
  }
  kOutputFile.flush();
  kOutputFile.close();
  kppOutputFile.flush();
  kppOutputFile.close();
  k2OutputFile.flush();
  k2OutputFile.close();
  return true;
};

}//namespace reader
}//namespace experiments
}//namespace kmeans
