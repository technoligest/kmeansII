
from lib.scripts.experiment_convex_hull import calcConvexHull, calcConvexHullArea
from lib.scripts.experiment_utils import distance
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
    self.totalDistance = 0
    self._convexHull = None
    self._area = None
    for p in pointPositions:
      self.totalDistance += distance(Cluster.dataset[p], centre)


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
