
//#include "handlers/dataReader.h"
#include <iostream>
#include "Algorithm/Kmeans.hh"
#include "Algorithm/IterationRunners.hh"
#include "Algorithm/SeedPickers.hh"
#include "handlers/dataReader.hh"


using namespace std;

int main(int argc, char **argv) {
  Dataset d = readFile(
          "/Users/Technoligest/Documents/Classes/Current/Norbert + Vlado/kmeansII/inputFiles/DimREdFullData.txt");
//  cout << d << endl;
//  KmeansArgs args;
//  if (!args.parse_args(argc, argv)) {
//    cout << "Could not parse arguments. Try again." << endl;
//    return 1;
//  }
//  KmeansBase *k = readArgs(args);
  Dataset centres;
  KmeansBase *t = new KmeansInitializer<RandomSeedPicker, LiyoidsIteration>();
  KmeansBase *t2 = new Kmeans<LiyoidsIteration>();
  KmeansBase *k = new KmeansII<LiyoidsIteration,LiyoidsIteration>();
  cout << k->cluster(d, centres, 10) << endl;


//  if (k == NULL) {
//    cout << "Could not create Kmeans object. Try again." << endl;
//    return 1;
//  }
//  Dataset d = readFile(args.inputFileName);
//  vector<Instance> centres;
//
//  for(auto &i:centres) {
//    std::cout << i<<endl;
//  }
//
//  cout << sqrt(k->cluster(d, centres, args.k))<<endl;
//
//  delete k;
  cout << "finished" << endl;
  return 0;
}
