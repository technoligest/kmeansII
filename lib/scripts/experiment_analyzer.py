#!/usr/bin/python
"""
Analyzer class contain functions that help calculate difference measures
to see the accuracy of a clustering algorithm.
"""
import lib.scripts.strongly_connected_componenents as scc
import math
import lib.scripts.experiment_perfect_matching as hung
import lib.scripts.experiment_utils as utils
import numpy as np

class Analyzer:
  def __init__(self, experiments, dataset):
    """
    :param experiments: the experiments run on the dataset. Assuming they are all independant
    :param dataset: The dataset the experiments were run on.
    """
    self.experiments = sorted(experiments, key=lambda experiment:experiment.totalDistanceToCentres)
    self.dataset = dataset
    self._NIDs = None
    self.matchings = None

  @property
  def NIDs(self):
    """
    :return:the normalized information distances of all the experiments
    """
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
    """
    :param experiment: the experiment to do the calculations on
    :return: the entropy for that experiment
    """
    n = len(self.dataset)
    result = 0
    for cluster in experiment.clusters:
      clusterSize = len(cluster.pointPositions)
      result += clusterSize / n * math.log((clusterSize / n), 2)
    return -1 * result


  def mutualInformation(self, mat):
    """
    Information Theory mutual information calculation
    :param mat:
    :return:
    """
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
    """
    :return: self.matchings[expId1][expId2][k] = the matching for cluster k in self.experiments[expId1] with self.experiments[expId2]
    """
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



  def calcNIDs(self):
    """
    normalized information distance between every experiement and the experiment with the lowest objective function i.e.
  experiments[0]
    :return:
    """
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

  def genUniqueRandom(self, size, low, high):
    result = []
    while len(result)<size:
      temp = np.random.randint(low,high)
      while temp in result:
        temp = np.random.randint(low,high)
      result.append(temp)
    return result


  def cliques(self):
    """
    :return:  The number of cliques of given size result[i] = number of cliques of size i+1 of i+1 randomly chosen experiments

    """
    if len(self.experiments)<2:
      return None
    result = []
    for i in range(1,len(self.experiments[0].clusters)):
      result.append(self._calcClique(self.genUniqueRandom(i+1,0,len(self.experiments[0].clusters))))
    return result


  def _calcClique(self, arr):
    """
    :param arr: an array which includes all the experiments indices that
  are to be evaluated for the clique.
    :return: the number of cliques iof size len(arr) inside of the experiments
  specified by their indices in arr
    """
    if self.matchings == None:
      self.calcMatchings()
    nodesDict = dict()
    for eIndex in arr:
      eIndex = int(eIndex)
      assert eIndex < len(self.experiments)
      assert eIndex >= 0
      for clusterId in range(len(self.experiments[eIndex].clusters)):
        nodesDict[(eIndex, clusterId)] = scc.Node((eIndex, clusterId))

    for eIndex, clusterId in nodesDict:
      for e2Index in arr:
        if e2Index == eIndex:
          continue
        assert (eIndex < len(self.matchings))
        assert (e2Index < len(self.matchings[eIndex]))
        assert (clusterId < len(self.matchings[eIndex][e2Index]))
        key = (e2Index, self.matchings[eIndex][e2Index][clusterId])
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



