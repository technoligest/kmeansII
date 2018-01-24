from lib.scripts.experiment_convex_hull import calcConvexHull, calcConvexHullArea
from lib.scripts.experiment_utils import distance
import lib.scripts.experiment_utils as utils
"""
A cluster is a centre, and collection of opoint positions.
Cluster objects rely on the Cluter class for having the dataset saved in order to be able to make sense of the clusterPositions
"""
class Cluster:
  def __init__(self, centre, pointPositions):
    assert hasattr(Cluster, 'dataset')
    assert len(centre) == 2
    self.centre = centre
    self.pointPositions = pointPositions
    self._pointPositionsInBinary = None
    self.totalDistance = 0
    self._convexHull = None
    self._area = None
    for p in pointPositions:
      self.totalDistance += distance(Cluster.dataset[p], centre)
    self._calcPointPositionsInBinary()


  """
  The convex hull of the cluster is represented as a set of points sorted counter clockwise
  """
  @property
  def convexHull(self):
    if self._convexHull == None:
      points = [Cluster.dataset[p] for p in self.pointPositions]
      self._convexHull = calcConvexHull(points)
    return self._convexHull

  @property
  def area(self):
    if self._area == None:
      self._area = calcConvexHullArea(self.convexHull)
    return self._area

  @property
  def binaryPointPositions(self):
    return self._pointPositionsInBinary

  def _calcPointPositionsInBinary(self):
    _pointPositionsInBinary = 1
    tempPos = 0
    for i in range(len(Cluster.dataset)):
      _pointPositionsInBinary=_pointPositionsInBinary << 1
      if tempPos < len(self.pointPositions) and i == self.pointPositions[tempPos]:
        _pointPositionsInBinary += 1
        tempPos += 1
    self._pointPositionsInBinary = _pointPositionsInBinary

