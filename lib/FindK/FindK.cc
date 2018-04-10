//
// Created by Yaser Alkayale on 2018-04-09.
//
#include<vector>
#include <iostream>
#include <unordered_map>
#include "../algorithm/kmeans.h"
#include "hungarian.h"
#include<thread>
#include <mutex>

using std::cout;
using std::endl;
using std::string;
using kmeans::operator<<;
using ull=unsigned long long;

using std::thread;

constexpr int thread_count = 9;

std::vector<kmeans::Dataset> runExperiments(kmeans::Dataset &dataset, int maxK) {
  std::vector<kmeans::Dataset> centres(maxK);
  std::vector<thread> threads;
  std::mutex centres_mutex;
  auto run = [&](ull tid) {
    for(ull i = tid; i < maxK; i += thread_count) {
      kmeans::Dataset tempCentres;
      kmeans::Kmeanspp<> kmeanspp;
      kmeanspp.cluster(dataset, maxK, tempCentres);
      std::lock_guard<std::mutex> guard(centres_mutex);
      centres[i] = tempCentres;
    }
  };
  for(int i = 0; i < thread_count; ++i) {
    threads.push_back(thread(run, i));
  }

  for(auto &t:threads) {
    t.join();
  }
  return centres;
}

std::vector<std::vector<ull>> calcPointPositions(const kmeans::Dataset &dataset, const kmeans::Dataset &centres) {
  std::vector<std::vector<ull>> positions(centres.size(), std::vector<ull>());
  ull currCandidate;
  double minDistance;
  double tempDistance;
  for(int instanceId = 0; instanceId < dataset.size(); ++instanceId) {
    currCandidate = 0;
    minDistance = std::numeric_limits<double>::max();
    for(int centreId = 0; centreId < centres.size(); ++centreId) {
      tempDistance = kmeans::utils::distanceSquared(dataset[instanceId], centres[centreId]);
      if(minDistance > tempDistance) {
        minDistance = tempDistance;
        currCandidate = centreId;
      }
    }
    positions[currCandidate].push_back(instanceId);
  }
  return positions;
}

ull overlap(std::vector<ull> list1, std::vector<ull> list2) {
  std::sort(list1.begin(), list1.end());
  std::sort(list2.begin(), list2.end());
  std::vector<int> v_intersection;
  std::set_intersection(list1.begin(), list1.end(), list2.begin(), list2.end(), std::back_inserter(v_intersection));
  return v_intersection.size();
}

std::vector<std::vector<double>>
overlapMatrix(const std::vector<std::vector<ull>> &pos1, const std::vector<std::vector<ull>> &pos2) {
  std::vector<std::vector<double>> overlaps;
  for(auto positions2:pos2) {
    std::vector<double> overlapTemp;
    for(auto positions1:pos1) {
      overlapTemp.push_back(overlap(positions1, positions2));
    }
    overlaps.push_back(overlapTemp);
  }
  return overlaps;
}

std::unordered_map<string, std::vector<ull>>
calcMatchings(const kmeans::Dataset &dataset, const std::vector<kmeans::Dataset> &centres) {
  std::vector<thread> threads;
  std::unordered_map<string, std::vector<ull>> matchings;
  std::vector<std::vector<std::vector<ull>>> centrePositions;
  std::mutex matchings_mutex;

  for(ull centreId = 0; centreId < centres.size(); ++centreId) {
    centrePositions.push_back(calcPointPositions(dataset, centres[centreId]));
  }

  std::vector<std::atomic<int>> positionsFreeCount(centres.size());


  for(ull centre1Id = 0; centre1Id < centres.size() - 1; ++centre1Id) {
    for(ull centre2Id = centre1Id + 1; centre2Id < centres.size(); ++centre2Id) {
      threads.push_back(thread([=, &centrePositions, &matchings, &positionsFreeCount, &matchings_mutex]() {
        const auto &overlaps = overlapMatrix(centrePositions[centre1Id], centrePositions[centre2Id]);

        ++positionsFreeCount[centre1Id];
        ++positionsFreeCount[centre2Id];
        if(positionsFreeCount[centre1Id] == centres.size() - 1) {
          centrePositions[centre1Id] = {};
        }
        const auto &matching = hungarian::maximumWeightPerfectMatching(overlaps);
        std::vector<ull> currMatching;
        for(auto match:matching) {
          currMatching.push_back(match.first);
        }
        std::string id = std::to_string(centre1Id) + "_" + std::to_string(centre2Id);
        std::lock_guard<std::mutex> guard(matchings_mutex);
        matchings[id] = currMatching;

      }));
    }

  }
  for(auto &thread:threads) {
    thread.join();
  }
  return matchings;
};

struct Node{
public:
  std::string name;
  std::vector<Node *> neighbours;
  bool visited;

  Node() {}

  explicit Node(std::string n) : name(n), visited(false) {}

  explicit Node(const Node &n) : name(n.name), neighbours(n.neighbours), visited(n.visited) {}

};

std::ostream &operator<<(std::ostream &o, const Node &n) {
  o << "[";
  for(auto neighbour:n.neighbours) {
    o << neighbour->name << ", ";
  }
  o << "]" << endl;
  return o;
}

template<typename T>
std::ostream &operator<<(std::ostream &o, const std::vector<T> &v) {
  o << "[";
  for(auto i :v) {
    o << i << ", ";
  }
  if(!v.empty()) {
    o << v[v.size() - 1];
  }
  o << "]" << endl;
  return o;
}

std::unordered_map<std::string, std::unique_ptr<Node>>
buildGraph(std::unordered_map<string, std::vector<ull>> matchings, int maxK) {
  assert(!matchings.empty());
  std::unordered_map<std::string, std::unique_ptr<Node>> nodes;
  for(ull runId = 0; runId < maxK; ++runId) {
    for(ull clusterId = 0; clusterId < maxK; ++clusterId) {
      std::string nodeId = std::to_string(runId) + "_" + std::to_string(clusterId);
      nodes[nodeId] = std::make_unique<Node>(nodeId);
    }
  }
  string centres1id, centres2id;

  for(auto matching:matchings) {
    ull delimPos = matching.first.find("_");
    centres1id = matching.first.substr(0, delimPos);
    centres2id = matching.first.substr(delimPos + 1, matching.first.size());
    for(int clusterId = 0; clusterId < maxK; ++clusterId) {
      auto &n1 = nodes[centres1id + "_" + std::to_string(clusterId)];
      auto &n2 = nodes[centres2id + "_" + std::to_string(matching.second[clusterId])];
      n1->neighbours.push_back(n2.get());
      n2->neighbours.push_back(n1.get());
    }
  }
  return nodes;
}

ull componentSize(Node *n) {
  if(n->visited) {
    return 0;
  }
  n->visited = true;
  ull size = 1;
  for(auto neighbour: n->neighbours) {
    size += componentSize(neighbour);
  }
  return size;
}

ull componentSize(std::unique_ptr<Node> &n) {
  if(n->visited) {
    return 0;
  }
  n->visited = true;
  ull size = 1;
  for(auto neighbour: n->neighbours) {
    size += componentSize(neighbour);
  }
  return size;
}

std::vector<std::vector<ull>> sizes;

std::vector<ull> computeComponentSizes(std::unordered_map<std::string, std::unique_ptr<Node>> &graph) {
  std::vector<ull> sizes;
  for(auto &node: graph) {
    if(!node.second->visited) {
      sizes.push_back(componentSize(node.second));
    }
  }
  return sizes;
}

ull findK(kmeans::Dataset dataset, int maxK) {
  double totalTime = 0;

  for(int i = maxK; i > 1; --i) {
    auto currTime = std::chrono::system_clock::now();
    auto centres = runExperiments(dataset, i);
    auto matchings = calcMatchings(dataset, centres);

    auto graph = buildGraph(matchings, i);

    auto componentSizes = computeComponentSizes(graph);

    std::cout << "Finding k for k: " << i << endl;
    std::cout << componentSizes << std::endl;
    std::chrono::duration<double> diff = std::chrono::system_clock::now() - currTime;
    std::cout << "FindK ran in: " << diff.count() << endl << endl;
    totalTime += diff.count();
  }
  std::cout << "Total Time: " << totalTime << endl;
  return 0;
}


int main(int argc, char **argv) {
  if(argc < 3) {
    cout << "Usage: ./findK <inputFilename> <maxK>" << endl;
    exit(1);
  }
  string fileName = argv[1];
  int k = std::atoi(argv[2]);


  //string fileName = "/Users/yaseralkayale/Documents/classes/current/honours/kmeansII/generatedFiles/datasets/dataset0.csv";
  ////fileName = "/Users/yaseralkayale/Documents/classes/current/honours/kmeansII/finalDatasets/dimred";
  //int k = 30;
  std::ifstream file(fileName);
  kmeans::Dataset dataset = kmeans::readCSVDataset(file);
  ull newk = findK(dataset, k);
  cout << newk << endl;
  return 0;
}
