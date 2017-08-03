"""
centre
pointpositions
convexHull
Area
TotalDistance to centre

"""
from convex_hull import calcConvexHull, calcConvexHullArea
from distance import distance


class Cluster:
    def __init__(self, centre, pointPositions):
        assert hasattr(Cluster, 'dataset')
        assert len(centre) == 2
        self.centre = centre
        self.pointPositions = pointPositions
        points = [Cluster.dataset[p] for p in pointPositions]
        self.convexHull = calcConvexHull(points)
        self.area = calcConvexHullArea(self.convexHull)
        self.totalDistance = 0
        for p in pointPositions:
            self.totalDistance += distance(Cluster.dataset[p], centre)
