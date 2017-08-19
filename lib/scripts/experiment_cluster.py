"""
centre
pointpositions
convexHull
Area
TotalDistance to centre

"""
from lib.scripts.experiment_convex_hull import calcConvexHull, calcConvexHullArea
from lib.scripts.experiment_utils import distance

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
