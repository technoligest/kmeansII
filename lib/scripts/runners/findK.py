import os
import subprocess
import numpy as np
import lib.scripts.experiment_utils as utils
from lib.scripts.experiment_perfect_matching import minimum_weight_perfect_matching, maximum_weight_perfect_matching
import matplotlib.pyplot as plt
import sys
from threading import Thread, Lock

def calcPointPositions(dataset, centres):
  result = [[] for _ in range(len(centres))]
  for instId in range(len(dataset)):
    currCandidateCentreId = 0
    minDistance = sys.float_info.max
    for centreId in range(len(centres)):
      currDistance = utils.distance(dataset[instId], centres[centreId])
      if minDistance > currDistance:
        minDistance = currDistance
        currCandidateCentreId = centreId
    result[currCandidateCentreId].append(instId)
  return result


def fastAdjacencyMatrix(c1, c2):
  assert (len(c1) == len(c2))
  closestCentrePositions = []
  for cluster in c1:
    distances = [utils.distance(cluster.centre, cluster2.centre) for cluster2 in c2]
    distances = [(i, distances[i]) for i in range(len(distances))]
    closestCentrePositions.append(sorted([x for x, y in sorted(distances, key=lambda x:x[1])[:1]])[:2])
  result = []
  for centre2Index in range(len(c1)):
    row = []
    for centre1Index in range(len(c2)):
      if centre2Index in closestCentrePositions[centre1Index]:
        row.append(utils.overlap(c1[centre1Index].pointPositions, c2[centre2Index].pointPositions))
      else:
        row.append(0)
    result.append(row)
  return result

class Node:
  def __init__(self, name):
    self.name = name
    self.neighbours = []
    self.visited = False

  @property
  def size(node):
    if node.visited:
      return 0
    node.visited = True
    size = 1
    for neighbour in node.neighbours:
      size += neighbour.size
    return size

class FindK:
  def __init__(self, executable, maxk, inputFileName):
    self.maxk_ = maxk
    self.lock = Lock();
    self.dataset_ = np.loadtxt(inputFileName, float, delimiter=",");
    self.centres_ = self.runExperiments(inputFileName, maxk, executable);
  @utils.printRunningTime
  def solve(self):
    res = sorted([len(self.cliqueSizes(inputFileName, self.maxk_, executableName, self.dataset_)) for _ in range(10)])
    g = self.group(res)
    return [a for a, b in sorted(zip(g[0], g[1]), key=lambda z:z[1])][-1]
  @utils.printRunningTime
  def group(self, values):
    """
    :param values: an array of items
    :return: (vals, count), vals=the distict values in the array, count=the pairwise count of each distict value
    """
    values = np.array(sorted(values))
    dif = np.ones(values.shape, values.dtype)
    dif[1:] = np.diff(values)
    idx = np.concatenate((np.where(dif)[0], [len(values)]))
    vals = values[idx[:-1]]
    count = np.diff(idx)
    return (vals, count)
  def runExperiment(self, executableName, k, inputFileName, outputFileName, algorithm, l=None, r=None):
    if (algorithm == "kmeansII" or algorithm == "kmeansNew"):
      assert (l != None and r != None)
      p = subprocess.run(
        [executableName, "-i", inputFileName, "-k", str(k), "-a", algorithm, "-o", outputFileName, "-l", str(l), "-r",
         str(r)])
    else:
      p = subprocess.run(
        [executableName, "-i", inputFileName, "-k", str(k), "-a", algorithm, "-o", outputFileName])
    if p.returncode != 0:
      exit("Shit went wrong. Check what happened.")
  @utils.printRunningTime
  def runExperiments(self, inputFileName, k, executable):
    """
    :param inputFileName: of the dataset to be clustered. CSV dataset required.
    :param k: The number of clusters for k-means++ clustering.
    :param executable:
    :return: the centres of all the experiments
    """
    tempFile = "aaaaaaaatemp"
    for i in range(k):
      self.runExperiment(executable, k,
                         inputFileName=inputFileName,
                         outputFileName=tempFile + str(i),
                         algorithm="kmeans++")
    centres = []
    for i in range(k):
      centres.append(np.loadtxt(tempFile + str(i), float, delimiter=","))
    # Deleting all the temporary files.
    for i in range(k):
      os.remove(tempFile + str(i))
      os.remove(tempFile + str(i) + ".extra")
    return centres
  @utils.printRunningTime
  def calcMatchings(self):
    threads = []
    matchings = dict()
    lock = Lock()
    @utils.printRunningTime
    def calcMatching(dataset, centres, centres1Id, centres2Id):
      # print("Started matching.")
      centres1 = centres[centres1Id]
      centres2 = centres[centres2Id]
      pos1 = calcPointPositions(dataset, centres1)
      pos2 = calcPointPositions(dataset, centres2)
      distances = utils.adjacencyMatrix(pos1, pos2, lambda p1, p2:len(np.intersect1d(np.array(p1), np.array(p2))));
      matching = maximum_weight_perfect_matching(distances)
      lock.acquire()
      matchings[(centres1Id, centres2Id)] = [a for a, _ in matching]
      lock.release()
      # print("Ended matching.")
    for centres1Id in range(len(self.centres_) - 1):
      for centres2Id in range(centres1Id + 1, len(self.centres_)):
        thread = Thread(target=calcMatching, args=(self.dataset_, self.centres_, centres1Id, centres2Id))
        threads.append(thread)
        thread.start()
    for thread in threads:
      thread.join()
    # plt.figure();
    # for m in matching:
    #   x, y = utils.splitIntoXY([centres2[m[0]], centres1[m[1]]])
    #   plt.plot(x, y, marker='o', fillstyle='full', markeredgewidth=0)
    result = matchings
    return result

  @utils.printRunningTime
  def buildGraph(self, matchings, numRuns):
    if len(matchings) == 0:
      return None
    size = len(next(iter(matchings.values())))
    for i in matchings:
      assert (len(matchings[i]) == size)
    nodes = dict()
    for runId in range(numRuns):
      for clusterId in range(size):
        nodeId = (runId, clusterId)
        nodes[nodeId] = Node(nodeId)

    for matchingId in matchings:
      centres1id, centres2id = matchingId
      matching = matchings[matchingId]
      for runId in range(numRuns):
        node1 = nodes[(centres1id, runId)]
        node2 = nodes[(centres2id, matching[runId])]
        node1.neighbours.append(node2)
        node2.neighbours.append(node1)
    return nodes

  @utils.printRunningTime
  def cliqueSizes(self, inputFileName, k, executable, dataset):
    centres = self.runExperiments(inputFileName, k, executable)  # set of all centres over all runs
    matchings = self.calcMatchings()
    graph = self.buildGraph(matchings, k)
    cliqueSizes = [graph[subgraphName].size for subgraphName in graph if not graph[subgraphName].visited]
    print(cliqueSizes)
    return cliqueSizes


import time
curr = time.time()
executableName = "/Users/yaseralkayale/Documents/classes/current/honours/kmeansII/cmake-build-debug/kmeans"
k = 6
inputFileName = "/Users/yaseralkayale/Documents/classes/current/honours/kmeansII/generatedFiles/datasets/dataset0.csv"
print("The answer is: ", FindK(executableName, k, inputFileName).solve())
print(time.time() - curr)
# centres  =[1]*6
# i=0
# for centres1Id in range(len(centres) - 1):
#   for centres2Id in range(centres1Id + 1, len(centres)):
#     i+=1
# print(i)
