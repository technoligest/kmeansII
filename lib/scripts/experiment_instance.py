#!/usr/bin/python
"""
clusters
centres
averages(distance/area)[]
distance
"""
from experiment_cluster import *
from experiment_distances import distance
import sys


class ExperimentInstance:
  """
  returns an array of arrays corresponding to the point positions of every centre
  in the experiment run. These pointpositions are disjoint and are calculated based
  on the closest points to each centre.
  """

  def calcPointPositions(self):
    result = [[] for _ in range(len(self.centres))]
    for instId in range(len(ExperimentInstance.dataset)):
      currCandidateCentreId = 0
      minDistance = sys.float_info.max
      for centreId in range(len(self.centres)):
        currDistance = distance(ExperimentInstance.dataset[instId], self.centres[centreId])
        if minDistance > currDistance:
          minDistance = currDistance
          currCandidateCentreId = centreId
      result[currCandidateCentreId].append(instId)
    return result

  def __init__(self, centres, algorithm, distanceToCentres, timeToPickSeeds, numIterations, timeToRunIterations):
    assert hasattr(ExperimentInstance, 'dataset')
    self.centres = centres
    self.algorithm = algorithm
    self.distanceToCentres = distanceToCentres
    self.timeToPickSeeds = timeToPickSeeds
    self.numIterations = numIterations
    self.timeToRunIterations = timeToRunIterations
    self.clusters = []
    Cluster.dataset = ExperimentInstance.dataset
    pointPositions = self.calcPointPositions()
    for centre, p in zip(self.centres, pointPositions):
      self.clusters.append(Cluster(centre, p))
    self.averageDistanceOverArea = [c.totalDistance / c.area for c in self.clusters]
    print(self.averageDistanceOverArea)

  def centresToString(self):
    result = ""
    for inst in self.centres:
      result += str(inst[0]) + " " + str(inst[1]) + "\n"
    return result

  def __str__(self):
    return (">>>Start Experiment\n" +
            "algorithm:" + self.algorithm + "\n"
                                            "Sum of distance squared to centre:" + str(
      self.distanceToCentres) + "\n" +
            "Time to pick the seeds:" + str(self.timeToPickSeeds) + "\n" +
            "Number of iterations run:" + str(self.numIterations) + "\n" +
            "Time to run the iterations:" + str(self.timeToRunIterations) + "\n" +
            "Start Centres:\n" + self.centresToString() +
            "End Centres:\n" +
            "End Experiment:"
            )
