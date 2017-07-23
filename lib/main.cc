
//#include "handlers/dataReader.h"
#include <iostream>
#include <fstream>
#include "algorithm/kmeans.h"
#include "experiments/experiments.h"
#include "handlers/data_reader.h"


#define NumIterations 100


using namespace std;

void startTest();

int main(int argc, char **argv) {
  ifstream inputFile;
  inputFile.open("../inputFiles/DimRedFullData.txt");
  kmeans::Dataset d = kmeans::readDataset(inputFile);
  using kmeans::operator<<;
  std::cout << d << std::endl;
  kmeans::experiments::ExperimentRunner e(d,50);
  e.runExperiments(1);
  auto result = e.getExperiments();
  kmeans::experiments::reader::printExperiments("DimRedFullData",result);
  return 0;
}

void startTest() {

//  string filePath = "/Users/Technoligest/Documents/Classes/Current/Norbert + Vlado/kmeansII/inputFiles/DimREdFullData.txt";
//  Dataset d = readFile(filePath);
//
//  using ResultVector = vector<tuple<Dataset, double, ull, ull >>;
//  ResultVector kmeansResults;
//  ResultVector kmeansppResults;
//  ResultVector kmeansIIResults;
//
//  Dataset centres;
//  KmeansBase *kmeans = new Kmeans<LloydIterationRunner>();
//  KmeansBase *kmeanspp = new Kmeanspp<LloydIterationRunner>();
////  cout << k->cluster(d, centres, 100) << endl;
//  for (ull k = 10; k <= 100; k += 10) {
//    KmeansBase *kmeansII = new KmeansII<LloydIterationRunner, LloydIterationRunner>(k);
//    for (int i = 0; i < NumIterations; ++i) {
//      ull startTime = static_cast<ull>(time(nullptr));
//      double Distance = kmeans->cluster(d, centres, k);
//      ull t = static_cast<ull>(time(nullptr)) - startTime;
//      kmeansResults.push_back(tuple<Dataset, double, ull, ull>(centres, dist, t, k));
//
//
//      startTime = static_cast<ull>(time(nullptr));
//      dist = kmeanspp->cluster(d, centres, k);
//      t = static_cast<ull>(time(nullptr)) - startTime;
//      kmeansppResults.push_back(tuple<Dataset, double, ull, ull>(centres, dist, t, k));
//
//      startTime = static_cast<ull>(time(nullptr));
//      dist = kmeansII->cluster(d, centres, k);
//      t = static_cast<ull>(time(nullptr)) - startTime;
//      kmeansIIResults.push_back(tuple<Dataset, double, ull, ull>(centres, dist, t, k));
//    }
//    delete kmeansII;
//  }


  cout << "finished" << endl;
  return;

//  delete kmeans;
//  delete kmeanspp;
}
