//
// Created by Yaser Alkayale on 2017-07-04.
//

#ifndef KMEANSII_EXPERIMENTRUNNER_HH
#define KMEANSII_EXPERIMENTRUNNER_HH

#include "../Algorithm/data.hh"
#include "experimentResult.hh"
#include "../Algorithm/Kmeans.hh"
#include <dirent.h>

/*
 * Very messy implemntation to help us find the final number of th etest ran
 * This will help us guarantee not overwriting previous tests.
 */
namespace kmeans{
namespace experiments{
namespace helpers{
inline ull lastNumberedFile(const std::string directory, std::string prefix){
  cout << "prefix" << prefix << endl;
  DIR *dir;
  struct dirent *ent;
  ull nextNum = 0;
  if((dir = opendir(directory.c_str())) != NULL){
    /* print all the files and directories within directory */
    while((ent = readdir(dir)) != NULL){
      string temp = ent->d_name;
      cout << temp << endl;
      ull tempNextNum = 0;
      if(temp.substr(0, prefix.size()) == prefix){
        if(nextNum == 0){
          nextNum = 1;
        }
        string nextNumString = "";
        for(int i = prefix.size(); i < temp.size(); ++i){
          try{
            stoi(string(1, ent->d_name[i]));
            nextNumString += string(1, ent->d_name[i]);
          }
          catch(std::invalid_argument e){
            break;
          }
        }
        try{
          tempNextNum = stoull(nextNumString) + 1;
        }
        catch(std::invalid_argument e){
          cout << "Something went out in finding the right number of the new file. (Parsing the final num)" << endl;
        }
      }
      if(tempNextNum > nextNum){
        nextNum = tempNextNum;
      }
    }
    closedir(dir);
  } else{
    /* could not open directory */
    perror("");
    return EXIT_FAILURE;
  }
  return nextNum;
}
}//namespace helpers

class ExperimentRunner{
private:
  KmeansData::Dataset d;
  ull k;

  vector <ExperimentResult> results;

  inline void runAlg(KmeansBase *kmeans, string algName){
    KmeansData::Dataset centres;
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
  ExperimentRunner(KmeansData::Dataset &_d, ull _k) : d(_d), k(_k){};

  ExperimentRunner(KmeansData::Dataset &&_d, ull _k) : d(_d), k(_k){};

  ExperimentRunner(vector <ExperimentResult> &r) : results(r){};

  inline vector <ExperimentResult> getExperiments() const{
    return results;
  }

  inline void RunExperiments(ull numExperiments){
    KmeansBase *kmeans;
    kmeans = new Kmeans<LloydIterationRunner>();
    for(ull i = 0; i < numExperiments; ++i){
      runAlg(kmeans, "Kmeans");
    }
    delete kmeans;

    kmeans = new Kmeanspp<LloydIterationRunner>();
    for(ull i = 0; i < numExperiments; ++i){
      runAlg(kmeans, "Kmeans++");
    }
    delete kmeans;

    kmeans = new KmeansII<LloydIterationRunner, LloydIterationRunner>(2 * k, 5);
    for(ull i = 0; i < numExperiments; ++i){
      runAlg(kmeans, "Kmeans||");
    }
    delete kmeans;
  }


  inline bool printResult(std::string dataSetName){
    /*
     * Finding the next number to enter for the test
     * Taking the max of the 3 prefixes for each of the algorithms.
     */
    string dir = "/Users/Technoligest/Documents/Classes/Current/Norbert + Vlado/kmeansII/lib/Experiments/Experiment Results";
    ull num = std::max(ExperimentRunnerHelpers::lastNumberedFile(
            dir, "kmeans-" + dataSetName + "-test"), std::max(ExperimentRunnerHelpers::lastNumberedFile(dir,
                                                                                                        "kmeans++-" +
                                                                                                        dataSetName +
                                                                                                        "-test"),
                                                              ExperimentRunnerHelpers::lastNumberedFile(dir,
                                                                                                        "kmeans||-" +
                                                                                                        dataSetName +
                                                                                                        "-test")));


    string postFix = "-" + dataSetName + "-test" + to_string(num) + ".txt";
    ofstream kOutputFile(dir + "/kmeans" + postFix);
    ofstream kppOutputFile(dir + "/kmeans++" + postFix);
    ofstream k2OutputFile(dir + "/kmeans||" + postFix);
    for(const auto &i: results){
      if(i.algorithm == "Kmeans"){
        kOutputFile << i << endl;
      } else if(i.algorithm == "Kmeans++"){
        kppOutputFile << i << endl;
      } else if(i.algorithm == "Kmeans||"){
        k2OutputFile << i << endl;
      }
    }
    kOutputFile.flush();
    kOutputFile.close();
    kppOutputFile.flush();
    kppOutputFile.close();
    k2OutputFile.flush();
    k2OutputFile.close();
    return true;
  }
};
} // namspace experiments
} // namespace kmeans

#endif //KMEANSII_EXPERIMENTRUNNER_HH
