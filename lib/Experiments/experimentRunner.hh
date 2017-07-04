//
// Created by Yaser Alkayale on 2017-07-04.
//

#ifndef KMEANSII_EXPERIMENTRUNNER_HH
#define KMEANSII_EXPERIMENTRUNNER_HH

#include "../handlers/data.hh"
#include "experimentResult.hh"
#include "../Algorithm/Kmeans.hh"

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

  ExperimentRunner(vector<ExperimentResult> &r) : results(r){};

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
#endif //KMEANSII_EXPERIMENTRUNNER_HH
