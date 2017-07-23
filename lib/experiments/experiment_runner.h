//
// Created by Yaser Alkayale on 2017-07-04.
//

#ifndef KMEANSII_EXPERIMENTRUNNER_HH
#define KMEANSII_EXPERIMENTRUNNER_HH

#include <dirent.h>
#include "../algorithm/kmeans_data.h"
#include "../algorithm/kmeans.h"
#include "experiment_result.h"
#include "experiment_helpers.h"

/*
 * Very messy implemntation to help us find the final number of th etest ran
 * This will help us guarantee not overwriting previous tests.
 */
namespace kmeans{
namespace experiments{

class ExperimentRunner{
private:
  Dataset d;
  ull k;

  std::vector<ExperimentResult> results;
  void runAlg(KmeansBase *kmeans, const std::string &algName);


public:
  ExperimentRunner(Dataset &_d, ull _k) : d(_d), k(_k) {};
  ExperimentRunner(Dataset &&_d, ull _k) : d(_d), k(_k) {};
  ExperimentRunner(std::vector<ExperimentResult> &r) : results(r) {};
  inline std::vector<ExperimentResult> getExperiments() const { return results; }
  void runExperiments(ull numExperiments);
};

} // namspace experiments
} // namespace kmeans

#endif //KMEANSII_EXPERIMENTRUNNER_HH
