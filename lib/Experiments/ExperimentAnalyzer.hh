//
// Created by Yaser Alkayale on 2017-06-27.
//

#ifndef KMEANSII_EXPERIMENTANALYZER_HH
#define KMEANSII_EXPERIMENTANALYZER_HH

#include "experiments.hh"

class ExperimentAnalyzer{
private:
  ExperimentRunner er;
public:
  inline ExperimentAnalyzer(ExperimentRunner &_er):er(_er){}
  inline void RunAnalyzer(){

  }
};
#endif //KMEANSII_EXPERIMENTANALYZER_HH
