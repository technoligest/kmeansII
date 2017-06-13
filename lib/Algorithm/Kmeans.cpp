//
// Created by Yaser Alkayale on 2017-05-29.
//

#include "Kmeans.h"
#include <math.h>
#include <random>
#include <cassert>
using namespace std;
Kmeans::Kmeans() {}

Kmeans::~Kmeans() {}

namespace KmeansSolver {
//checks that all of the instances in the dataset are of teh same size
 bool analyzeDataset(Dataset &d) {
   for (Instance i:d) {
     if (i.size() != d[0].size()) {
       return false;
     }
   }
   return true;
 }

//fills the vector of centres with random points from the Dataset
 bool setRandomCentres(Dataset &d, std::vector<Instance> &centres) {
   if (d.empty() || centres.empty() || d.size() < centres.size()) {
     return false;
   }

   std::random_device rd;
   std::mt19937 gen(rd());
   std::uniform_real_distribution<> dis(0, 1);

   int n = d.size();
   int k = centres.size();
   for (int i = 0; i < k; ++i) {
     centres[i] = d[static_cast<int>((dis(gen) * n))];
   }

   return true;
 }

//squared euclidean distance
 double findDistanceSquared(const Instance &r1, const Instance &r2) {
   if (r1.size() != r2.size())
     return -1;
   double result = 0;
   size_t size = r1.size();
   for (int i = 0; i < size; ++i) {
     result += pow(r1[i] - r2[i], 2);
   }
   return result;
 }


 double runLiyodIteration(Dataset &d, std::vector<Instance> &centres) {
   if (d.empty() || centres.empty() || d.size() < centres.size()) {
     return -1;
   }

   double totalDistance = 0;
   size_t n = d.size();           //the number of items in the dataset
   size_t k = centres.size();     //the number of clusters
   size_t m = centres[0].size();  //the size of each row

   std::vector<Instance> newCentres(k);
   std::vector<size_t> newCentreSizes(k);

   //resetting all the values
   std::fill(newCentreSizes.begin(), newCentreSizes.end(), 0);
   for (auto &centre:newCentres) {
     centre.resize(m);
     std::fill(centre.begin(), centre.end(), 0);
   }

   //adding each instance to where it belongs
   for (Instance &inst: d) {
     assert(centres.size() == k);
     int minDistClusterId = 0;
     double minDist = findDistanceSquared(inst, centres[0]);
     for (int i = 1; i < k; ++i) {
       Instance &centre = centres[i];
       double newDist = findDistanceSquared(inst, centre);
       if (newDist < minDist) {
         minDist = newDist;
         minDistClusterId = i;
       }
     }
     assert(newCentres[minDistClusterId].size() == m);
     for (int i = 0; i < m; ++i) {
       newCentres[minDistClusterId][i] += inst[i];
     }
     newCentreSizes[minDistClusterId] += 1;
     totalDistance += minDist;
   }

   //recalculating the right centres
   for (int i = 0; i < k; ++i) {
     auto &centre = newCentres[i];
     for (auto &point: centre) {
       if (newCentreSizes[i] != 0) {
         point /= newCentreSizes[i];
       }
     }
   }
   centres = newCentres;
   return totalDistance;
 }

//runs all the necessary iterations to complete the clustering
//returns the total distance squared of the best iteration
 double runLiyodIterations(Dataset &d, std::vector<Instance> &centres) {
   if (d.empty() || centres.empty() || d.size() < centres.size()) {
     return -1;
   }


   std::vector<Instance> bestCentres;

   double currDistance = std::numeric_limits<double>::max();
   double bestDistance = std::numeric_limits<double>::max();
   int iteration;
   for (iteration = 0; iteration < MAX_NUM_ITERATIONS; ++iteration) {
     std::cout << "starting it:" << std::endl;

     double newDistance = runLiyodIteration(d, centres);
     for (auto &i:centres) {
       std::cout << i << std::endl;
     }
     if (newDistance < bestDistance) {
       bestDistance = newDistance;
       bestCentres = centres;
     }
     if (newDistance > currDistance * LOCAL_ITERATION_BIAS) {
       std::cout << "Terminating because iteration is exceeded local bias." << std::endl;
       break;
     }
     if (fabs(newDistance - currDistance) < 1e-6) {
       std::cout << "Terminating because iterations are stable." << std::endl;
       break;
     }
     currDistance = newDistance;
     std::cout << "ending it." << std::endl;
   }
   std::cout << "numIterations: " << iteration << std::endl;
   return bestDistance;
 }

 bool prepareForClustering(Dataset &d, std::vector<Instance> &centres, ull k) {
   if (d.empty() || d.size() < k || k < 1) {
     std::cout << "Cannot cluster data with empty dataset or one with too few values of k values of less than 1.";
     return false;
   }

   //check that the dataset is all of the same size
   if (!analyzeDataset(d)) {
     std::cout << "cannot cluster data that is not consistene";
     return false;
   }

   int n = d.size(); //the number of items in our dataset
   int m = d[0].size(); //size of each instance in the dataset;s

   //resizing the centres vector to the right size.  i.e. the given number k
   centres.resize(k);

   //resizing all of the centres to the right size;
   for (Instance i:centres) {
     i.resize(m);
   }
   return true;
 }
}


using namespace KmeansSolver;

//function returns the sum of squared distance of the centroids it finds.
double Kmeans::cluster(Dataset &d, std::vector<Instance> &centres, ull k) {
  if (!prepareForClustering(d, centres, k)) {
    return -1;
  }

  //set random centres from the given dataset
  if (!setRandomCentres(d, centres)) {
    std::cout << "Could not generate random centres";
    return -1;
  }

  return runLiyodIterations(d, centres);
}









