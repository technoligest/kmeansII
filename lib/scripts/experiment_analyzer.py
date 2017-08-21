#!/usr/bin/python
import math

from lib.scripts.experiment_instance import ExperimentInstance
import lib.scripts.experiment_utils as utils
class ExperimentAnalyzer:
  def __init__(self, experiments, dataset):
    self.experiments = sorted(experiments, lambda experiment:experiment.distanceToCentres)
    self.dataset = dataset
    self.calcARIs()
    self.calcMutualInformations()
    print("Created analyzer class")

  @property
  def timeToRunIterations(self):
    return [exp.timeToRunIterations for exp in self.experiments]

  @property
  def totalDistanceToCentres(self):
    return [exp.distanceToCentre for exp in self.experiments]

  @property
  def numIterations(self):
    return [exp.numIterations for exp in self.experiments]

  def calcMutualInformation(self, cluster1, cluster2):
    mat = [[utils.overlap(a, b) for a in cluster1.pointPositions] for b in cluster2.pointPositions]
    n = len(self.dataset)
    assert (n > 0)
    rowSums = [sum(row) for row in mat]
    colSums = [0] * len(mat[0])
    for rowId in range(len(mat)):
      for colId in range(len(mat[0])):
        colSums[colId] += mat[rowId][colId]

    result = 0
    for i in len(mat):
      for j in len(mat[0]):
        result += mat[i][j] / n * math.log(((mat[i][j] / n) / ((rowSums[i] * colSums[j]) / (n * n))), 2)
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
      self.ARIs.append((self.experiments[0], a, self.calcARI(self.experiments[0], a.clusters)))
  def calcMutualInformations(self):
    if len(self.experiments) % 2 != 0:
      del self.experiments[len(self.experiments - 1)]
    self.MI = []
    for a in self.experiments:
      self.MI.append((self.experiments[0], a, self.calcMutualInformation(self.experiments[0], a)))
