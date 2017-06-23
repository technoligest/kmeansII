
//#include "handlers/dataReader.h"
#include <iostream>
#include "Algorithm/Kmeans.hh"
#include "handlers/dataReader.hh"

#define NumIterations 100


using namespace std;
void startTest();

int main(int argc, char **argv) {
  string filePath = "/Users/Technoligest/Documents/Classes/Current/Norbert + Vlado/kmeansII/inputFiles/DimREdFullData.txt";
  Dataset d = readFile(filePath);
  Dataset centres;
  ull k = 50;
  KmeansBase *kmeans = new KmeansII<LiyoidsIteration, LiyoidsIteration>(10);
  cout << kmeans->cluster(d, centres, k);
  return 0;
}

void startTest() {
  string filePath = "/Users/Technoligest/Documents/Classes/Current/Norbert + Vlado/kmeansII/inputFiles/DimREdFullData.txt";
  Dataset d = readFile(filePath);

  using ResultVector = vector<tuple<Dataset, double, ull, ull >>;
  ResultVector kmeansResults;
  ResultVector kmeansppResults;
  ResultVector kmeansIIResults;

  Dataset centres;
  KmeansBase *kmeans = new Kmeans<LiyoidsIteration>();
  KmeansBase *kmeanspp = new Kmeanspp<LiyoidsIteration>();
//  cout << k->cluster(d, centres, 100) << endl;
  for (ull k = 10; k <= 100; k += 10) {
    KmeansBase *kmeansII = new KmeansII<LiyoidsIteration, LiyoidsIteration>(k);
    for (int i = 0; i < NumIterations; ++i) {
      ull startTime = static_cast<ull>(time(nullptr));
      double dist = kmeans->cluster(d, centres, k);
      ull t = static_cast<ull>(time(nullptr)) - startTime;
      kmeansResults.push_back(tuple<Dataset, double, ull, ull>(centres, dist, t, k));


      startTime = static_cast<ull>(time(nullptr));
      dist = kmeanspp->cluster(d, centres, k);
      t = static_cast<ull>(time(nullptr)) - startTime;
      kmeansppResults.push_back(tuple<Dataset, double, ull, ull>(centres, dist, t, k));

      startTime = static_cast<ull>(time(nullptr));
      dist = kmeansII->cluster(d, centres, k);
      t = static_cast<ull>(time(nullptr)) - startTime;
      kmeansIIResults.push_back(tuple<Dataset, double, ull, ull>(centres, dist, t, k));
    }
    delete kmeansII;
  }


  cout << "finished" << endl;

  delete kmeans;
  delete kmeanspp;
}
