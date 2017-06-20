
#include "handlers/dataReader.h"


using namespace std;

int main(int argc, char **argv) {
  Dataset d = readFile(
          "/Users/Technoligest/Documents/Classes/Current/Norbert + Vlado/kmeansII/inputFiles/DimREdFullData.txt");
//  cout << d << endl;
  KmeansArgs args;
  if (!args.parse_args(argc, argv)) {
    cout << "Could not parse arguments. Try again." << endl;
    return 1;
  }
  KmeansBase *k = readArgs(args);
  if (k == NULL) {
    cout << "Could not create Kmeans object. Try again." << endl;
    return 1;
  }
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
