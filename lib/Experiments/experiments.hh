//
// Created by Yaser Alkayale on 2017-06-26.
//
#include <cxxabi.h>
#include <fstream>
#include "../Algorithm/Kmeans.hh"

#ifndef KMEANSII_EXPERIMENTS_HH
#define KMEANSII_EXPERIMENTS_HH
using namespace std;
struct ExperimentResult{
  string algorithm;     //name of the algorithm used for clustering
  Dataset centres;      //The centres of the result after running the algorithm
  ull numIterations;    //The number of iteration it took to converge to get the centres
  dist distanceSquared; //total distance squared from the centres to the closest points to it
  ull seedPickerTime;   //time it took to pick the seeds
  ull iterationTime;    //time it took to run the iterations;
};

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

inline Dataset readCentres(std::istream file){
  Dataset result;
  while(file.good()){
    string line;
    std::getline(file, line);
    if(line.substr(0, 3) == "End"){
      return result;
    }
    std::stringstream lineStream(line);
    std::string item;
    Instance i;
    while(std::getline(lineStream, item, ' ')){
      try{
        i.push_back(stod(item));
      }
      catch(std::invalid_argument e){
        std::cout << "Invalid entry in the centres.";
      }
    }
    result.push_back(i);
  }
  result.clear();
  return result;
};

inline ExperimentResult readExperimentBody(std::istream file){
  string line;
  ExperimentResult result;
  while(file.good()){
    string delimed;
    getline(file, line, ':');
    if(line == "Algorithm"){
      std::getline(file, line);
      result.algorithm = line.substr(1);
    } else if(line == "Sum of distance squared to centre"){
      std::getline(file, line);
      result.algorithm = line.substr(1);
    } else if(line == "Time to pick the seeds"){
      std::getline(file, line);
      try{
        result.seedPickerTime = stoull(line.substr(1));
      }
      catch(std::invalid_argument e){
        std::cout << "Invalid File Input for Time to pick the seeds." << endl;
      }
    } else if(line == "Number of iterations run"){
      std::getline(file, line);
      try{
        result.numIterations = stoull(line.substr(1));
      }
      catch(std::invalid_argument e){
        std::cout << "Invalid File Input for number of iterations run." << endl;
      }
    } else if(line == "Time to run the iterations"){
      std::getline(file, line);
      try{
        result.iterationTime = stoull(line.substr(1));
      }
      catch(std::invalid_argument e){
        std::cout << "Invalid File Input for time to run iterations." << endl;
      }
    } else if(line == "Start Centres"){
      std::getline(file, line);
      result.centres = readCentres(file);
    } else if(line.substr(0, 3) == "<<<"){
      return result;
    }
  }
  result.distanceSquared = -1;
  result.centres.clear();
  result.iterationTime = -1;
  result.numIterations = 0;
  result.algorithm = "NOTHINg";
  result.seedPickerTime = 0;
  return result;
}


inline vector<ExperimentResult> readExperiments(std::istream file){
  vector<ExperimentResult> result;

  while(file.good()){
    string line;
    std::getline(file,line);
    if(line.substr(0, 3) == ">>>"){
      result.push_back(readExperimentBody(file));
    }
  }
}

class ExperimentRunner{
private:
  Dataset d;
  ull k;

  vector<ExperimentResult> results;

  inline void runAlg(KmeansBase *kmeans, string algName){
    Dataset centres;
    ExperimentResult e;
    kmeans->cluster(d, centres, k);
    int status;
    e.algorithm = algName;
    e.centres = centres;
    e.numIterations = kmeans->numIterations();
    e.distanceSquared = kmeans->distanceSquared();
    e.seedPickerTime = kmeans->seedPickerTime();
    e.iterationTime = kmeans->iterationRunnerTime();
    results.push_back(e);
  }


public:
  ExperimentRunner(Dataset &_d, ull _k) : d(_d), k(_k){};

  ExperimentRunner(Dataset &&_d, ull _k) : d(_d), k(_k){};

  inline vector<ExperimentResult> getExperiments() const{
    return results;
  }

  inline void RunExperiments(ull numExperiments){
    KmeansBase *kmeans;
    kmeans = new Kmeans<LloydsIteration>();
    for(ull i = 0; i < numExperiments; ++i){
      runAlg(kmeans, "Kmeans");
    }
    delete kmeans;

    kmeans = new Kmeanspp<LloydsIteration>();
    for(ull i = 0; i < numExperiments; ++i){
      runAlg(kmeans, "Kmeans++");
    }
    delete kmeans;

    kmeans = new KmeansII<LloydsIteration, LloydsIteration>(2 * k, 5);
    for(ull i = 0; i < numExperiments; ++i){
      runAlg(kmeans, "Kmeans||");
    }
    delete kmeans;
  }

  inline bool printResult(string fileName){
    using namespace std;
    ofstream outputFile(fileName);
    for(const auto &i: results){
      outputFile << i << endl;
    }
    return true;
  }
};


#endif //KMEANSII_EXPERIMENTS_HH
