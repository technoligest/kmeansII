
#include "handlers/dataReader.h"
#include <math.h>
using namespace std;

int main(int argc, char **argv) {
  KmeansArgs args;
  if (!args.parse_args(argc, argv)) {
    cout << "Could not parse arguments. Try again." << endl;
    return 1;
  }
  Kmeans *k = readArgs(args);
  if (k == NULL) {
    cout << "Could not create Kmeans object. Try again." << endl;
    return 1;
  }
  Dataset d = readFile(args.inputFileName);
  vector<Instance> centres;

  for(auto &i:centres) {
    std::cout << i<<endl;
  }

  cout << sqrt(k->cluster(d, centres, args.k))<<endl;

  delete k;
  return 0;
}
