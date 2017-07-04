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
   out << "***Start Centres" << endl;
   out << e.centres << endl;
   out << "<<<End Experiment" << endl;
   return out;
 }

 //inline ExperimentRunner readExperiment(std::string fileNames){
 //
 //}
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
  inline vector<ExperimentResult> getExperiments()const {
    return results;
  }
  inline void RunExperiments(ull numExperiments){
    KmeansBase *kmeans;
    kmeans = new Kmeans<LloydsIteration>();
    for(ull i = 0; i < numExperiments; ++i){
      runAlg(kmeans, "Kmeans");
    }
    delete kmeans;

    kmeans =new Kmeanspp<LloydsIteration>();
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
