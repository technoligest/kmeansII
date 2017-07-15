//
// Created by Yaser Alkayale on 2017-06-27.
//

#ifndef KMEANSII_EXPERIMENTANALYZER_HH
#define KMEANSII_EXPERIMENTANALYZER_HH


#include "experiment_runner.h"

namespace kmeans{
namespace experiments{
class ExperimentAnalyzer{
private:
  const std::vector<ExperimentResult> er;  //the experiments that were run
  Dataset d;                    //the data which the experiments were run on

  /*
   * First Index: The index of the first experiment
   * Second Index: The index of the second experiment
   * Martix: This gives us the intersections between the
   */
  Matrix<Matrix<Index>> clusterIntersections;


  std::vector<std::vector<Distance>> circumferences;
  //refer to diagram in Diagrams + Notes/ExperimentAnalysisDiagramDraft.pdf
  std::vector<std::vector<ull>> clusterUnion;


  /*
   * This is the total distance squared/the circumference of the tightest square around the data(The data in that cluster, not the
   * Only works for 2-d data
   * It is calculated for each one of the experiments run.
   */
  std::vector<double> distanceOverCircumference;


  /*
   * Each item in this std::vector is the average intersection/Union of each centre compared to all others
   * For each centre: Intersection is the number of points found in all centres
   * For each centre: Union is the sum of sizes of all centres minus the intersection
   */
  double intersectionOverUnion;

  inline double calcDistanceOverCircumference() {
    if(er.size() < 2) {
      return -1;
    }
    assert (er[0].centres.size() == 2);
    Instance topPoint{std::numeric_limits<DataType>::min(), 0};
    Instance bottomPoint{std::numeric_limits<DataType>::max(), 0};
    Instance rightPoint{0, std::numeric_limits<DataType>::min()};
    Instance leftPoint{0, std::numeric_limits<DataType>::max()};

    for(const auto &experiment: er) {
      topPoint = {std::numeric_limits<DataType>::min(), 0};
      bottomPoint = {std::numeric_limits<DataType>::max(), 0};
      rightPoint = {0, std::numeric_limits<DataType>::min()};
      leftPoint = {0, std::numeric_limits<DataType>::max()};
      for(const auto inst: experiment.centres) {
        assert(inst.size() == 2);
        if(inst[0] > topPoint[0]) {
          topPoint = inst;
        }
        if(inst[0] < bottomPoint[0]) {
          bottomPoint = inst;
        }
        if(inst[1] > rightPoint[1]) {
          rightPoint = inst;
        }
        if(inst[1] < leftPoint[1]) {
          leftPoint = inst;
        }
      }
      Distance circumference = 2 * (::kmeans::helpers::findDistanceSquared(topPoint, bottomPoint) +
                                    ::kmeans::helpers::findDistanceSquared(rightPoint, leftPoint));
      distanceOverCircumference.push_back(circumference / experiment.distanceSquared);
    }

    assert(distanceOverCircumference.size() == er.size());
    return 0; //XXXXX
  }

  inline double calCintersectionOverUnion() {
    if(er.size() < 2) {
      return -1;
    }
    Dataset tempIntersectionCentres = er[0].centres;

    for(int i = 1; i < er.size(); ++i) {
      ExperimentResult r = er[i];
      /*
       * Very bad O(k^2) Implementation to find the intersection between all the centres
       */
      for(auto i1 = tempIntersectionCentres.begin(); i1 != tempIntersectionCentres.end(); ++i1) {
        for(auto i2: r.centres) {
          if(isSameCentre(*i1, i2)) {
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

  inline bool isSameCentre(const Instance &c1, const Instance &c2) {
    for(int i = 0; i < c1.size(); ++i) {
      if(c1[i] == c2[i]) {
        return false;
      }
    }
    return true;
  }

  inline bool AnalyzeExperiments() {
    if(er.empty()) {
      return true;
    }
    size_t size = er[0].centres.size();
    for(auto &i:er) {
      if(i.centres.size() != size) {
        return false;
      }
    }
    return true;
  }

  ///*
  // * given an experiment, calculate the belongings of all the points in it
  // * For Efficiency, the indexes of the points are stored rather than the points themselves.
  // */
  //
  //inline void calCluster(ExperimentResult &exp){
  //  exp.clusters.resize(exp.centres.size());
  //  for(Index instLocation = 0; instLocation < d.size(); ++instLocation){
  //    Instance &inst = d[instLocation];
  //    Index rightCentreLocation = -1;
  //    Distance lowestDistance = numeric_limits<double>::max();
  //    for(Index i = 0; i < exp.centres.size(); ++i){
  //      Distance currDistance = findDistanceSquared(exp.centres[i], inst);
  //      if(currDistance < lowestDistance){
  //        lowestDistance = currDistance;
  //        rightCentreLocation = i;
  //      }
  //    }
  //    if(rightCentreLocation == -1){
  //      std::cout << "Error. Could not add centre to cluster because nothing was available." << endl;
  //    } else{
  //      exp.clusters[rightCentreLocation].push_back(instLocation);
  //    }
  //  }
  //}

  inline void prepareExperiments() {
    //calculate the belongings of the points to their clsuters
    //for(auto exp:er){
    //  calCluster(exp);
    //}
    //clusterIntersections.resize(er.size(), std::vector<Matrix<Index>>(er.size()));
    //for(int i=1; i<er.size();++i){
    //  clusterIntersections[0].push_back(std::vector<Index>(i));
    //}
  }


  //Matrix<Index> calculateIntersections(int i, int j){
  //  auto centres1 = er[i].centres;
  //  auto centres2 = er[j].centres;
  //
  //  auto matchingMatrix = calcMatchingMatrix(centres1, centres2);
  //  return Matrix<unsigned long>();
  //}
  //
  //inline void calculateIntersections(){
  //  for(int i = 0; i < er.size(); ++i){
  //    for(int j = 0; j < er.size(); ++j){
  //      if(i == j){
  //        clusterIntersections[i][i] = er[i].clusters;
  //      }
  //      if(i>j){
  //        clusterIntersections[j][i] = clusterIntersections[i][j];
  //      }
  //      clusterIntersections[i][j] = calculateIntersections(i,j);
  //    }
  //  }
  //}

public:
  inline ExperimentAnalyzer(const std::vector<ExperimentResult> &_er, const Dataset &data) : er(_er),
                                                                                             d(data) { prepareExperiments(); }

  inline ExperimentAnalyzer(std::vector<ExperimentResult> &&_er, Dataset &&data) : er(move(_er)),
                                                                                   d(move(
                                                                                       data)) { prepareExperiments(); }

  inline ExperimentAnalyzer(std::vector<ExperimentResult> &&_er, const Dataset &data) : er(move(_er)),
                                                                                        d(data) { prepareExperiments(); }

  inline ExperimentAnalyzer(const std::vector<ExperimentResult> &_er, Dataset &&data) : er(_er),
                                                                                        d(move(
                                                                                            data)) { prepareExperiments(); }

  inline void RunAnalyzer() {
    //calcIntersections();

  }
};
} //namespace experiments
} //namespace kmeans

#endif //KMEANSII_EXPERIMENTANALYZER_HH
