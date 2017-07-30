
#include <iostream>
#include <fstream>
#include <random>
#include "experiments/experiments.h"
#include "handlers/data_reader.h"
#include "experiments/experiment_analyzer2.h"

using namespace std;

int main(int argc, char **argv) {
  //ifstream inputFile;
  //inputFile.open("../inputFiles/DimRedFullDataComplete.txt");
  //kmeans::Dataset d = kmeans::readDataset(inputFile);
  //inputFile.close();
  //auto i = kmeans::experiments::calculateConvexHull(d);
  //ofstream outputFile("TESTING CONVEX HULL.txt");
  //using kmeans::operator<<;
  //std::function<double(kmeans::Instance)> lam = [](const kmeans::Instance &w)->double { ;
  //  if(!w.empty()) return w[0];
  //  return std::numeric_limits<double>::min();
  //};
  //std::cout << "Area of the hull: "<<kmeans::experiments::convexHullArea(i) << std::endl;
  //kmeans::experiments::helpers::mergeSort(i, lam);
  //for(auto inst:i) {
  //  outputFile << inst << std::endl;
  //}
  //
  //outputFile.flush();
  //outputFile.close();

  //ifstream inputFile;
  //inputFile.open("../inputFiles/DimRedFullDataComplete.txt");
  //kmeans::Dataset d = kmeans::readDataset(inputFile);
  //inputFile.close();
  //kmeans::experiments::ExperimentRunner e(d, 50);
  //e.runExperiments(2);
  //auto i = e.getExperiments();
  //kmeans::experiments::reader::printExperiments("DimRedFullData.txt",i);
  ifstream inputFile;
  inputFile.open(
      "/Users/Technoligest/Documents/Classes/Current/Norbert + Vlado/kmeansII/lib/experiments/Experiment Results/kmeans++-DimRedFullDataComplete.txt-test0.txt");


  //inputFile.open("/Users/Technoligest/Documents/Classes/Current/Norbert + Vlado/kmeansII/lib/experiments/Experiment Results/kmeans++-DimRedFullData.txt-test2.txt");
  auto experiments = kmeans::experiments::reader::readExperiments(inputFile);
  inputFile.close();

  inputFile.open(
      "/Users/Technoligest/Documents/Classes/Current/Norbert + Vlado/kmeansII/inputFiles/DimRedFullDataComplete.txt");
  auto dataset = kmeans::readDataset(inputFile);
  std::cout << experiments.size() << std::endl;
  kmeans::experiments::ExperimentAnalyzer2 analyzer(experiments, dataset);


  //kmeans::Matrix<kmeans::Distance> matrix{{0, 0,  0,  0},
  //                                        {0, 12, 15, 8},
  //                                        {0, 15, 17, 1},
  //                                        {0, 8,  3,  11}};
  //matrix = {
  //    {1,2,3},
  //    {3,1,2},
  //    {3,2,1}
  //};
  ////
  //matrix = {
  //    {0,0,0},
  //    {0,1,2},
  //    {0,3,4}
  //};
  //auto result = kmeans::experiments::minimumWeightPerfectMatching(matrix);
  //
  //for(const auto &i:result) {
  //  std::cout << std::get<0>(i)<<", "<<std::get<1>(i) << "\t";
  //}

  //std::queue<int> testingArr;
  //testingArr.push(1);
  //testingArr.push(2);
  //testingArr.push(3);
  //std::cout<<testingArr.front()<<std::endl;
  //testingArr.pop();
  //std::cout<<testingArr.front()<<std::endl;
  //testingArr.pop();
  //std::cout<<testingArr.front()<<std::endl;
  //testingArr.pop();
  return 0;
}
