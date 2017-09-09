//
// Created by Yaser Alkayale on 2017-07-04.
//

#ifndef KMEANSII_EXPERIMENTRESULT_HH
#define KMEANSII_EXPERIMENTRESULT_HH

#include "../algorithm/kmeans_data.h"
#include "../algorithm/kmeans_io.h"

namespace kmeans{
namespace experiments{

struct ExperimentResult{
  std::string algorithm;             //name of the algorithm used for clustering
  Dataset centres;                   //The centres of the result after running the algorithm
  ull numIterations;                 //The number of iteration it took to converge to get the centres
  Distance distanceSquared;          //total distance squared from the centres to the closest points to it
  ull seedPickerTime;                //time it took to pick the seeds
  ull iterationTime;                 //time it took to run the iterations;
  std::vector<double> clusterAreas;  //the area of covex cull of each cluster
};

/*
 * Experiment has to start with >>>
 * Every "command" has to be followed by ':'
 * Some commands might be followed by additional information.
 */
inline std::ostream &operator<<(std::ostream &out, const ExperimentResult &e) {
  out << ">>>Start Experiment" << std::endl;
  out << "algorithm: " << e.algorithm << std::endl;
  out << "Sum of distance squared to centre: " << e.distanceSquared << std::endl;
  out << "Time to pick the seeds: " << e.seedPickerTime << std::endl;
  out << "Number of iterations run: " << e.numIterations << std::endl;
  out << "Time to run the iterations: " << e.iterationTime << std::endl;
  out << "Start Centres:" << std::endl;
  using kmeans::operator<<;
  out << e.centres << std::endl;
  out << "End Centres:" << std::endl;
  out << "End Experiment:" << std::endl;
  return out;
}

} //namespace experiments
} //namespace kmeans
#endif //KMEANSII_EXPERIMENTRESULT_HH
