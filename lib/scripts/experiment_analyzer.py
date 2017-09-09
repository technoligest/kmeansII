#!/usr/bin/python
"""
"""
import lib.scripts.strongly_connected_componenents as scc
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

  """
  @:return list of Normalized Information Distance which corresponds to each experiment in sorted order
  """
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


  """
  Information Theory entropy calculations
  """
  def entropy(self, experiment):
    n = len(self.dataset)
    result = 0
    for cluster in experiment.clusters:
      clusterSize = len(cluster.pointPositions)
      result += clusterSize / n * math.log((clusterSize / n), 2)
    return -1 * result

  """
  Information Theiry mutual information calculation
  """
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

  """
  self.matchings[expId1][expId2][k] = the matching for cluster k in sefl.experiments[expId1] with self.experiments[expId2]
  """
  @utils.printRunningTime
  def calcMatchings(self):
    self.matchings = [[[] for _ in range(len(self.experiments))] for _ in range(len(self.experiments))]
    for i in range(len(self.experiments)):
      for j in range(i + 1, len(self.experiments)):
        # mat = utils.adjacencyMatrix(self.experiments[i].clusters, self.experiments[j].clusters,
        #                             lambda a, b:bin(a.binaryPointPositions & b.binaryPointPositions).count("1") - 1)
        mat = utils.fastAdjacencyMatrix(self.experiments[i].clusters, self.experiments[j].clusters)
        currentMatchings = hung.maximum_weight_perfect_matching(mat)
        self.matchings[i][j] = [x for x, y in currentMatchings]
        self.matchings[j][i] = [y for x, y in sorted(currentMatchings, key=lambda x:x[0])]
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
  @:param arr, an array which includes all the experiments indices that 
  are to be evaluated for the clique.
  
  @:return the number of cliques iof size len(arr) inside of the matches experients in arr. 
  """
  @utils.printRunningTime
  def calcClique(self, arr):
    if self.matchings == None:
      self.calcMatchings()
    if not isinstance(arr, list):
      return None
    nodesDict = dict()
    for eIndex in arr:
      assert eIndex < len(self.experiments)
      assert eIndex >= 0
      for clusterId in range(len(self.experiments[eIndex].clusters)):
        nodesDict[(eIndex, clusterId)] = scc.Node((eIndex, clusterId))

    for eIndex, clusterId in nodesDict:
      for k in arr:
        if k == eIndex:
          continue
        assert (eIndex < len(self.matchings))
        assert (k < len(self.matchings[eIndex]))
        assert (clusterId < len(self.matchings[eIndex][k]))
        key = (k, self.matchings[eIndex][k][clusterId])
        node = nodesDict[(eIndex, clusterId)]
        node.neighbours.append(nodesDict[key])
    l = []
    for key in nodesDict:
      l.append(nodesDict[key])
    componenets = scc.ConnectedComponents(l).calc()
    result = 0
    for component in componenets:
      if len(component) == len(arr):
        result += 1
    return result
