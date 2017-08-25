#!/usr/bin/python
"""
"""
import time
import math
import lib.scripts.experiment_perfect_matching as hung
import lib.scripts.experiment_utils as utils

class Analyzer:
  def __init__(self, experiments, dataset):
    self.experiments = sorted(experiments, key=lambda experiment:experiment.distanceToCentres)
    self.dataset = dataset
    self._NIDs = None
    self.matchings = None
    print("Created analyzer class")

  @property
  def NIDs(self):
    if self._NIDs == None:
      self.calcNIDs()
    return self._NIDs

  @property
  def iterationsRuntimes(self):
    return [exp.iterationsRuntimes for exp in self.experiments]

  @property
  def totalDistanceToCentres(self):
    return [exp.distanceToCentres for exp in self.experiments]

  @property
  def numIterations(self):
    return [exp.numIterations for exp in self.experiments]

  def entropy(self, experiment):
    n = len(self.dataset)
    result = 0
    for cluster in experiment.clusters:
      clusterSize = len(cluster.pointPositions)
      result += clusterSize / n * math.log((clusterSize / n), 2)
    return -1 * result


  def mutualInformation(self, mat):
    n = len(self.dataset)
    assert (n > 0)
    rowSums = [sum(row) for row in mat]
    colSums = [0] * len(mat[0])
    for rowId in range(len(mat)):
      for colId in range(len(mat[0])):
        colSums[colId] += mat[rowId][colId]
    result = 0
    for i in range(len(mat)):
      for j in range(len(mat[0])):
        if int(mat[i][j]) > 0:
          result += mat[i][j] / n * math.log(((mat[i][j] * n) / (rowSums[i] * colSums[j])), 2)
    return result


  def calcARI(self, cluster1, cluster2):
    mat = [[utils.overlap(a, b) for a in cluster1.pointPositions] for b in cluster2.pointPositions]
    assert (len(mat) > 0)

    index = 0
    for row in mat:
      for item in row:
        index += utils.ncr(item, 2)

    t1 = 0
    for row in mat:
      t1 += utils.ncr(sum(row), 2)

    colSums = [0] * len(mat[0])
    for rowId in range(len(mat)):
      for colId in range(len(mat[0])):
        colSums[colId] += mat[rowId][colId]

    t2 = 0
    for i in colSums:
      t2 += utils.ncr(i, 2)

    ExpectedIndex = t1 * t2 / utils.ncr(len(self.dataset), 2)
    MaxIndex = (t1 + t2) / 2

    return (index - ExpectedIndex) / (MaxIndex - ExpectedIndex)

  def calcARIs(self):
    if len(self.experiments) % 2 != 0:
      del self.experiments[len(self.experiments - 1)]
    self.ARIs = []
    for a in self.experiments:
      self.ARIs.append((self.experiments[0], a, self.calcARI(self.experiments[0].clusters, a.clusters)))

  def calcMutualInformations(self):
    if len(self.experiments) % 2 != 0:
      del self.experiments[len(self.experiments - 1)]
    self.MI = []
    for a in self.experiments:
      self.MI.append((self.experiments[0], a, self.calcMutualInformation(self.experiments[0].clusters, a.clusters)))

  @utils.printRunningTime
  def calcMatchings(self):
    self.matchings = [[None for _ in range(len(self.experiments))] for _ in range(len(self.experiments))]
    for i in range(len(self.experiments)):
      for j in range(i + 1, len(self.experiments)):
        start = time.time()
        mat = utils.adjacencyMatrix(self.experiments[i].clusters, self.experiments[j].clusters,
                                    lambda a, b:utils.overlap(a.pointPositions, b.pointPositions))
        currentMatchings = hung.maximum_weight_perfect_matching(mat)
        self.matchings[i][j] = [x for x, y in currentMatchings]
        self.matchings[j][i] = [y for x, y in sorted(currentMatchings, key=lambda x:x[0])]
        print(" ran in: ",(time.time()-start))
    print("finished calculating matchings for the analyzer")


  """
   normalized information distance between every experiement and the experiment with the lowest objective function i.e.
   experiments[0]
  """
  def calcNIDs(self):
    print("calculating NID's")
    self._NIDs = []
    exp1 = self.experiments[0]
    exp1Entropy = self.entropy(exp1)
    for i in range(1, len(self.experiments)):
      exp2 = self.experiments[i]
      matrix = utils.adjacencyMatrix(exp1.clusters, exp2.clusters,
                                     lambda c1, c2:utils.overlap(c1.pointPositions, c2.pointPositions))
      self._NIDs.append(1 - self.mutualInformation(matrix) / max([exp1Entropy, self.entropy(exp2)]))
      print(self.NIDs[len(self.NIDs) - 1])


  """
  result[i] stores the number of i-cliques
  arr is the set of experiments that we are looking at
  """
  def calcCliques(self, arr):
    if self.matchings == None:
      self.calcMatchings()
    matchingDict = dict()
    for e1index in arr:
      for k in range(len(self.experiments[e1index].clusters)):
        tempArr = []
        for e2index in arr:
          if e1index == e2index:
            tempArr.append(k)
            continue
          tempArr.append(self.matchings[e1index][e2index][k])
        key = self.listToString(tempArr)
        value = (e1index, k)
        if key in matchingDict:
          matchingDict[key].append(value)
        else:
          matchingDict[key] = [value]
    cliqueSize = len(arr)
    result = 0
    for i in matchingDict:
      if len(matchingDict[i]) == cliqueSize:
        result += 1
    return result