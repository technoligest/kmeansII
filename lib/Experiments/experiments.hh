//
// Created by Yaser Alkayale on 2017-06-26.
//
#include <cxxabi.h>
#include "../Algorithm/Kmeans.hh"

#ifndef KMEANSII_EXPERIMENTS_HH
#define KMEANSII_EXPERIMENTS_HH
using namespace std;
struct ExperimentResult{
  string algorithm;
  Dataset centres;
  ull numIterations;
  dist distanceSquared;
  ull seedPickerTime;
  ull iterationTime;
};

inline ostream &operator<<(ostream &out, const ExperimentResult &e){
  out << ">>>Start Experiment" << endl;
  out << "Algorithm: " << e.algorithm << endl;
  out << "Sum of distance squared to centre: " << e.distanceSquared << endl;
  out << "Time to pick the seeds: " << e.seedPickerTime << endl;
  out << "Number of iterations run: " << e.numIterations << endl;
  out << "Time to run the iterations: " << e.iterationTime << endl;
  out << "***Start Centres"<<endl;
  out << e.centres << endl;
  out << "<<<End Experiment" << endl;
  return out;
}

class ExperimentRunner{
private:
  Dataset d;
  ull k;

  vector<ExperimentResult> results;

  inline void runAlg(KmeansBase *kmeans){
    Dataset centres;
    ExperimentResult e;
    kmeans->cluster(d, centres, k);
    int status;
    e.algorithm = abi::__cxa_demangle(typeid(KmeansII<LloydsIteration, LloydsIteration>()).name(), 0, 0, &status);
    e.centres = centres;
    e.numIterations = kmeans->numIterations();
    e.distanceSquared = kmeans->distanceSquared();
    e.seedPickerTime = kmeans->seedPickerTime();
    e.iterationTime = kmeans->iterationRunnerTime();
    results.push_back(e);
  }

  inline void runExperiment(){
    KmeansBase *kmeans = new Kmeans<LloydsIteration>();
    runAlg(kmeans);
    delete kmeans;

    kmeans =new Kmeanspp<LloydsIteration>();
    runAlg(kmeans);
    delete kmeans;

    kmeans = new KmeansII<LloydsIteration, LloydsIteration>(2 * k, 5);
    runAlg(kmeans);
    delete kmeans;
  }


public:
  ExperimentRunner(Dataset &_d, ull _k) : d(_d), k(_k){};

  ExperimentRunner(Dataset &&_d, ull _k) : d(_d), k(_k){};

  inline void RunExperiments(ull numExperiments){
    for(ull i = 0; i < numExperiments; ++i){
      runExperiment();
    }
  }

  inline bool printResult(string fileName){
    using namespace std;
    ofstream outputFile(fileName);

    //outputFile << ">>>Start dataset to be clustered with k= " << k << endl;
    //outputFile << d << endl;
    //outputFile << "<<<End dataset to be clustered " << endl;

    for(const auto &i: results){
      outputFile << i << endl;
    }

    return true;
  }
};


#endif //KMEANSII_EXPERIMENTS_HH
