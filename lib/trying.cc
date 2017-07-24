
#include <iostream>
#include <fstream>
#include <random>
#include "experiments/experiments.h"
#include "handlers/data_reader.h"
#include "experiments/convex_hull.h"

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

  ifstream inputFile;
  inputFile.open("../inputFiles/DimRedFullDataComplete.txt");
  kmeans::Dataset d = kmeans::readDataset(inputFile);
  inputFile.close();
  kmeans::experiments::ExperimentRunner e(d, 50);
  e.runExperiments(2);
  auto i = e.getExperiments();
  kmeans::experiments::reader::printExperiments("DimRedFullData.txt",i);
  return 0;
}
