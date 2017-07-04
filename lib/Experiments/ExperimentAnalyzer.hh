//
// Created by Yaser Alkayale on 2017-06-27.
//

#ifndef KMEANSII_EXPERIMENTANALYZER_HH
#define KMEANSII_EXPERIMENTANALYZER_HH

#include "experiments.hh"
#include "experimentRunner.hh"

using namespace std;

class ExperimentAnalyzer{
private:
  vector<ExperimentResult> er;
  Dataset d;


  /*
   * This is the total distance squared/the circumference of the tightest square around the data
   * Only works for 2-d data
   * It is calculated for each one of the experiments run.
   */
  vector<double> distanceOverCircumference;


  /*
   * Each item in this vector is the average intersection/Union of each centre compared to all others
   * For each centre: Intersection is the number of points found in all centres
   * For each centre: Union is the sum of sizes of all centres minus the intersection
   */
  double intersectionOverUnion;

  inline double calcDistanceOverCircumference(){
    if(er.size() < 2){
      return -1;
    }
    assert (er[0].centres.size() == 2);
    Instance topPoint{std::numeric_limits<dataType>::min(), 0};
    Instance bottomPoint{std::numeric_limits<dataType>::max(), 0};
    Instance rightPoint{0, std::numeric_limits<dataType>::min()};
    Instance leftPoint{0, std::numeric_limits<dataType>::max()};

    for(const auto &experiment: er){
      topPoint = {std::numeric_limits<dataType>::min(), 0};
      bottomPoint = {std::numeric_limits<dataType>::max(), 0};
      rightPoint = {0, std::numeric_limits<dataType>::min()};
      leftPoint = {0, std::numeric_limits<dataType>::max()};
      for(const auto inst: experiment.centres){
        assert(inst.size() == 2);
        if(inst[0] > topPoint[0]){
          topPoint = inst;
        }
        if(inst[0] < bottomPoint[0]){
          bottomPoint = inst;
        }
        if(inst[1] > rightPoint[1]){
          rightPoint = inst;
        }
        if(inst[1] < leftPoint[1]){
          leftPoint = inst;
        }
      }
      dist circumference = 2 * (KmeansHelpers::findDistanceSquared(topPoint, bottomPoint) +
                                KmeansHelpers::findDistanceSquared(rightPoint, leftPoint));
      distanceOverCircumference.push_back(circumference / experiment.distanceSquared);
    }

    assert(distanceOverCircumference.size() == er.size());
  }

  inline double calCintersectionOverUnion(){
    if(er.size() < 2){
      return -1;
    }
    Dataset tempIntersectionCentres = er[0].centres;

    for(int i = 1; i < er.size(); ++i){
      ExperimentResult r = er[i];

      /*
       * Very bad O(k^2) Implementation to find the intersection between all the centres
       */
      for(auto i1 = tempIntersectionCentres.begin(); i1 != tempIntersectionCentres.end(); ++i1){
        for(auto i2: r.centres){
          if(isSameCentre(*i1, i2)){
            tempIntersectionCentres.erase(i1);
          }
        }
      }
    }
    ull intersection = tempIntersectionCentres.size();
    assert(!er.empty());
    ull un = er[0].centres.size() * er.size() - intersection;
    return intersectionOverUnion;
  };

  inline bool isSameCentre(const Instance &c1, const Instance &c2){
    for(int i = 0; i < c1.size(); ++i){
      if(c1[i] == c2[i]){
        return false;
      }
    }
    return true;
  }

  inline bool AnalyzeExperiments(){
    if(er.empty()){
      return true;
    }
    size_t size = er[0].centres.size();
    for(auto i:er){
      if(i.centres.size() != size){
        return false;
      }
    }
    return true;
  }

public:
  inline ExperimentAnalyzer(ExperimentRunner &_er, Dataset &data) : er(_er.getExperiments()),d(data){}

  inline void RunAnalyzer(){

  }
};

#endif //KMEANSII_EXPERIMENTANALYZER_HH
