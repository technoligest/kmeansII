//
// Created by Yaser Alkayale on 2017-07-04.
//

#ifndef KMEANSII_EXPERIMENTRESULT_HH
#define KMEANSII_EXPERIMENTRESULT_HH

#include "../handlers/data.hh"

using namespace std;

struct ExperimentResult{
  string algorithm;               //name of the algorithm used for clustering
  KmeansData::Dataset centres;                //The centres of the result after running the algorithm
  ull numIterations;              //The number of iteration it took to converge to get the centres
  KmeansData::dist distanceSquared;           //total distance squared from the centres to the closest points to it
  ull seedPickerTime;             //time it took to pick the seeds
  ull iterationTime;              //time it took to run the iterations;
};

/*
 * Experiment has to start with >>>
 * Every "command" has to be followed by ':'
 * Some commands might be followed by additional information.
 */
inline ostream &operator<<(ostream &out, const ExperimentResult &e){
  out << ">>>Start Experiment" << endl;
  out << "Algorithm: " << e.algorithm << endl;
  out << "Sum of distance squared to centre: " << e.distanceSquared << endl;
  out << "Time to pick the seeds: " << e.seedPickerTime << endl;
  out << "Number of iterations run: " << e.numIterations << endl;
  out << "Time to run the iterations: " << e.iterationTime << endl;
  out << "Start Centres:" << endl;
  out << e.centres << endl;
  out << "End Centres:" << endl;
  out << "End Experiment:" << endl;
  return out;
}

#endif //KMEANSII_EXPERIMENTRESULT_HH
