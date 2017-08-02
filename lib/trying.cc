
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


  inputFile.open("/home/yaser/CLionProjects/kmeansII/lib/experiments/Experiment Results/kmeans++-DimRedFullDataComplete.txt-test0.txt");
  auto experiments = kmeans::experiments::reader::readExperiments(inputFile);
  inputFile.close();

  inputFile.open(
      "/home/yaser/CLionProjects/kmeansII/inputFiles/DimRedFullDataComplete.txt");
  auto dataset = kmeans::readDataset(inputFile);
  std::cout << experiments.size() << std::endl;
  kmeans::experiments::ExperimentAnalyzer2 analyzer(experiments, dataset);


  return 0;
}
