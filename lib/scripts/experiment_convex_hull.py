import math
from lib.scripts.experiment_utils import distance
import lib.scripts.experiment_utils as utils
"""
def cosSquaredOfPolarAngle(origin, p1, p2):
    # if p2 == origin or p1 == origin:
    #     return -1
    result = (math.degrees(math.acos(((p1[0] - origin[0]) * (p2[0] - origin[0]) +
                                      (p1[1] - origin[1]) * (p2[1] - origin[1])) /
                                     (distance(origin, p1) *
                                      distance(origin, p2)))))
    return result

def isNotLeftTurn(rightPoint, origin, leftPoint):
    return (0 <= ((origin[1] - rightPoint[1]) * (leftPoint[0] - origin[0]) -
                  (origin[0] - rightPoint[0]) * (leftPoint[1] - origin[1])))


def check2dMatrix(matrix):
    assert (len(matrix) > 2)
    for i in matrix:
        assert (len(i) == 2)

def calcConvexHull(points):
    check2dMatrix(points)
    # The sorting makes my life easier for now, but it
    # is porbably a bad idea for the long run as it
    # is not efficient. It is used to find the lowest left point
    points = sorted(points, key=lambda l: l[0])
    points = sorted(points, key=lambda l: l[1])
    lowestRight = [points[0][0] + 5, points[0][1]]
    anglesToLowestPoint = [cosSquaredOfPolarAngle(points[0], lowestRight, points[id]) for id in range(len(points))]
    anglesToLowestPoint[0] = -1
    points = [l[0] for l in sorted(zip(points, anglesToLowestPoint), key=lambda pair: pair[1])]
    result = [points[0], points[1], points[2]]
    for i in range(3, len(points)):
        while isNotLeftTurn(result[len(result) - 2], result[len(result) - 1], points[i]):
            if len(result)<3:
                print("FUCK CONVEXHull")
            del result[len(result) - 1]
        result.append(points[i])
    return result
"""

"""
Assumes input as the output of the convexHull algorithm
Anything else will give problems. This is because the input is
expected to be sorted in order clockwise or counterclocwise.
"""
def calcConvexHullArea(convexHull):
  if len(convexHull) < 3:
    return 0
  result = 0
  for i in range(len(convexHull) - 1):
    result += (convexHull[i][0] * convexHull[i + 1][1] -
               convexHull[i][1] * convexHull[i + 1][0])
  result += (convexHull[len(convexHull) - 1][0] * convexHull[0][1] -
             convexHull[len(convexHull) - 1][1] * convexHull[0][0])
  return result


"""
New implementation
"""
def orientation(p, q, r):
  o = (q[1] - p[1]) * (r[0] - q[0]) - \
      (q[0] - p[0]) * (r[1] - q[1])
  if o == 0:
    return 0
  if o > 0:
    return 1
  if o < 0:
    return 2

def calcConvexHull(points):
  if len(points) < 3:
    return None
  leftMostPoint = 0
  for i in range(1, len(points)):
    if points[i][0] < points[leftMostPoint][0]:
      leftMostPoint = i
  p = leftMostPoint
  q = None
  result = []
  while True:
    result.append(points[p])
    q = (p + 1) % len(points);
    for i in range(len(points)):
      if orientation(points[p], points[i], points[q]) == 2:
        q = i
    p = q
    if p == leftMostPoint:
      break
  return result
