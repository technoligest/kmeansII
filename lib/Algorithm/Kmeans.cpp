//
// Created by Yaser Alkayale on 2017-05-29.
//

#include "Kmeans.h"
#include <math.h>
#include <random>

Kmeans::Kmeans(Table data, const int k) : _table(data), _k(k), _prevDistance(0), _currDistance(0),
                                          _numIterations(0), _sum_squared_distance(0) {}

Kmeans::~Kmeans() {
}

void Kmeans::run() {
  Kmeans::findCentres();
//    runLioydIterations();
//    runIteration();
}


void Kmeans::findCentres() {
  findRandomCentres();
}

//randomly assign centres to the clusters in result
void Kmeans::findRandomCentres() {
  if (_table.empty() || _k < 1) {
    return;
  }
  srand((unsigned) time(NULL)); //this is not the best way to randomize numbers
  size_t size = _table.size();
  for (int i = 0; i < _k; ++i) {
    _result.push_back(Cluster(*_table[rand() % size]));
  }

}

void Kmeans::runLioydIterations() {
  _currDistance = 0;
  _prevDistance = 0;
  do {
    runIteration();
  } while (!stable());
}

void Kmeans::runIteration() {
  std::cout << "Started iteration" << std::endl;
  //if we have no cluster centres, then we can't run the iterations.
  if (_result.size() == 0) {
    return;
  }

  clearClusterData();
  ++_numIterations;
  _prevDistance = _currDistance;
  _currDistance = 0;

  for (Row *row: _table.data) {
    double lowest_distance = findDistance(_result[0].centre, *row);
    int temp_i = 0;
    for (int i = 1; i < _result.size(); ++i) {
      double new_distance = findDistance(_result[i].centre, *row);
      if (new_distance < lowest_distance) {
        lowest_distance = new_distance;
        temp_i = i;
      }
    }
    _currDistance += lowest_distance;

    //add the row in the right cluster.
    _result[temp_i].values.add(row);
  }
  calcNewCentres();
  std::cout << "finished the iteration." << std::endl;
}


//euclidean distance
double Kmeans::findDistance(Row &r1, Row &r2) {
  return sqrt(findDistanceSquared(r1, r2));
}

//squared euclidean distance
double Kmeans::findDistanceSquared(Row &r1, Row &r2) {
  if (r1.size() != r2.size())
    return 0;
  double result = 0;
  size_t size = r1.size();
  for (int i = 0; i < size; ++i) {
    result += pow(r1[i] - r2[i], 2);
  }
  return result;
}

//calculates the centres for each of the clusters in the result.
void Kmeans::calcNewCentres() {
  std::cout << "calculating centres" << std::endl;
  _sum_squared_distance = 0;
  for (auto i: _result) {
    calCentre(i);
    _sum_squared_distance += i.sum_squared_distances;
  }
  std::cout << "finshed calculating centres" << std::endl;
}

//calculates the center for the given cluster by finding the mean of each column
//also calculates the sum of squared distances
void Kmeans::calCentre(Cluster &c) {
  c.resetCentre();
  Table t = c.values;
  if (t.empty()) {
    return;
  }
  for (Row *row : t.data) {
    for (int i = 0; i < row->size(); ++i) {
      c.centre[i] = c.centre[i] + (*row)[i] / t.size();
    }
  }

  //calculating the distances to each cluster
  c.sum_squared_distances = 0;
  for (auto i: c.values.data) {
    c.sum_squared_distances += findDistance(*i, c.centre);
  }
}

//this empties the values of all the clusters in the result, leaving the centres intact.
void Kmeans::clearClusterData() {
  for (Cluster cluster: _result) {
    cluster.values.clear();
  }
}

//this checks if the current sum of distances is equal to the previous sum of distances
bool Kmeans::stable() {
  return _currDistance == _prevDistance;
}


//returns the result to the user.
std::vector<Cluster> *Kmeans::getResult() {
  return &_result;
}

//returns the number of interations the algorithm took
unsigned long Kmeans::numIterations() const {
  return _numIterations;
}

double Kmeans::sum_squared_distance() const {
  return _sum_squared_distance;
}




















//new implementation


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

void Kmeans::runIteration() {
  std::cout << "Started iteration" << std::endl;
  //if we have no cluster centres, then we can't run the iterations.
  if (_result.size() == 0) {
    return;
  }

  clearClusterData();
  ++_numIterations;
  _prevDistance = _currDistance;
  _currDistance = 0;

  for (Row *row: _table.data) {
    double lowest_distance = findDistance(_result[0].centre, *row);
    int temp_i = 0;
    for (int i = 1; i < _result.size(); ++i) {
      double new_distance = findDistance(_result[i].centre, *row);
      if (new_distance < lowest_distance) {
        lowest_distance = new_distance;
        temp_i = i;
      }
    }
    _currDistance += lowest_distance;

    //add the row in the right cluster.
    _result[temp_i].values.add(row);
  }
  calcNewCentres();
  std::cout << "finished the iteration." << std::endl;
}
void calcCentres(Dataset &d, std::vector<Instance> &centres){
  std::vector<Instance> newCentres;

}

double runLiyodIteration(Dataset &d, std::vector<Instance> &centres) {
  if (d.empty() || centres.empty() || d.size() < centres.size()) {
    return -1;
  }
  double totalDistance = 0;
  int n = d.size();
  for (Instance &i: d) {
    double lowestDist = findDistanceSquared(i, centres[0]);
    for (Instance &centre:centres) {
      double newDist = findDistanceSquared(i, centre);
      if (newDist < lowestDist) {
        lowestDist = newDist;
      }
    }
    totalDistance+=lowestDist;
  }
  calcCentres(d,centres);
  return totalDistance;
}

double runLiyodIterations(Dataset &d, std::vector<Instance> &centres) {
  if (d.empty() || centres.empty() || d.size() < centres.size()) {
    return -1;
  }
  std::vector<Instance> bestCentres;
  double currDistance = 0;
  double bestDistance = std::numeric_limits<double>::max();
  for (int iteration = 0; iteration < MAX_NUM_ITERATIONS; ++iteration) {
    double newDistance = runLiyodIteration(d, centres);
    if (newDistance < bestDistance) {
      bestDistance = newDistance;
      bestCentres = centres;
    }
    if (newDistance > currDistance * LOCAL_ITERATION_BIAS || fabs(newDistance - currDistance) < 1e-6) {
      break;
    }
    currDistance = newDistance;
  }
}

//function returns the sum of squared distance of the centroids it finds.
virtual double Kmeans::cluster(Dataset &d, std::vector<Instance> &centres, ull k) {
  if (d.empty() || d.size() < k || k < 1) {
    return 0;
  }
  if (!analyzeDataset(d)) {
    return -1;
  }
  int n = d.size();
  int m = d[0].size(); //size of each instance in the dataset;s

  //resizing the centres vector to the right size.  i.e. the given numeber k
  centres.resize(k);

  //resizing all of the centres to the right size;
  for (Instance i:centres) {
    i.resize(m);
  }

  //set random centres from the given dataset
  if (!setRandomCentres(d, centres)) {
    return -1;
  }

  return runLioydIterations(d, centres);
}








