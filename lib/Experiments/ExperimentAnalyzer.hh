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
  const vector<ExperimentResult> er;  //the Experiments that were run
  KmeansData::Dataset d;                    //the data which the experiments were run on

  /*
   * First Index: The index of the first experiment
   * Second Index: The index of the second experiment
   * Martix: This gives us the intersections between the
   */
  KmeansData::Matrix<KmeansData::Matrix<Index>> clusterIntersections;


  vector<vector<KmeansData::dist>> circumferences;
  //refer to diagram in Diagrams + Notes/ExperimentAnalysisDiagramDraft.pdf
  vector<vector<ull>> clusterUnion;


  /*
   * This is the total distance squared/the circumference of the tightest square around the data(The data in that cluster, not the
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
    KmeansData::Instance topPoint{std::numeric_limits<KmeansData::dataType>::min(), 0};
    KmeansData::Instance bottomPoint{std::numeric_limits<KmeansData::dataType>::max(), 0};
    KmeansData::Instance rightPoint{0, std::numeric_limits<KmeansData::dataType>::min()};
    KmeansData::Instance leftPoint{0, std::numeric_limits<KmeansData::dataType>::max()};

    for(const auto &experiment: er){
      topPoint = {std::numeric_limits<KmeansData::dataType>::min(), 0};
      bottomPoint = {std::numeric_limits<KmeansData::dataType>::max(), 0};
      rightPoint = {0, std::numeric_limits<KmeansData::dataType>::min()};
      leftPoint = {0, std::numeric_limits<KmeansData::dataType>::max()};
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
      KmeansData::dist circumference = 2 * (KmeansHelpers::findDistanceSquared(topPoint, bottomPoint) +
                                KmeansHelpers::findDistanceSquared(rightPoint, leftPoint));
      distanceOverCircumference.push_back(circumference / experiment.distanceSquared);
    }

    assert(distanceOverCircumference.size() == er.size());
    return 0; //XXXXX
  }

  inline double calCintersectionOverUnion(){
    if(er.size() < 2){
      return -1;
    }
    KmeansData::Dataset tempIntersectionCentres = er[0].centres;

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

  inline bool isSameCentre(const KmeansData::Instance &c1, const KmeansData::Instance &c2){
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
    for(auto &i:er){
      if(i.centres.size() != size){
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
  //    dist lowestDistance = numeric_limits<double>::max();
  //    for(Index i = 0; i < exp.centres.size(); ++i){
  //      dist currDistance = KmeansHelpers::findDistanceSquared(exp.centres[i], inst);
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

  inline void prepareExperiments(){
    //calculate the belongings of the points to their clsuters
    //for(auto exp:er){
    //  calCluster(exp);
    //}
    //clusterIntersections.resize(er.size(), vector<Matrix<Index>>(er.size()));
    //for(int i=1; i<er.size();++i){
    //  clusterIntersections[0].push_back(vector<Index>(i));
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
  inline ExperimentAnalyzer(const vector<ExperimentResult> &_er, const KmeansData::Dataset &data) : er(_er),
                                                                                        d(data){ prepareExperiments(); }

  inline ExperimentAnalyzer(vector<ExperimentResult> &&_er, KmeansData::Dataset &&data) : er(move(_er)),
                                                                              d(move(data)){ prepareExperiments(); }

  inline ExperimentAnalyzer(vector<ExperimentResult> &&_er, const KmeansData::Dataset &data) : er(move(_er)),
                                                                                   d(data){ prepareExperiments(); }

  inline ExperimentAnalyzer(const vector<ExperimentResult> &_er, KmeansData::Dataset &&data) : er(_er),
                                                                                   d(move(data)){ prepareExperiments(); }

  inline void RunAnalyzer(){
    //calcIntersections();

  }
};

#endif //KMEANSII_EXPERIMENTANALYZER_HH
