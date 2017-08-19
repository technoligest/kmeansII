import math
import sys

"""
calculate the union of 2 numerical lists
"""
def overlap(l1, l2):
  l1 = sorted(l1)
  l2 = sorted(l2)
  l1Pos = 0
  l2Pos = 0
  maxSize = min(len(l1), len(l2))
  result = 0
  while l1Pos < maxSize and l2Pos < maxSize:
    if l1[l1Pos] == l2[l2Pos]:
      l1Pos += 1
      l2Pos += 1
      result += 1
    elif l1[l1Pos] > l2[l2Pos]:
      l2Pos += 1
    else:
      l1Pos += 1
  return result


"""
given 2 lists and a function. Calculate the adjavency matrix between these two lists
by applying the function on every pair from the two
-basically creating a complete bipartite graph of the 2 sets of points
"""
def adjacencyMatrix(l1, l2, func):
  result = []
  for i2 in l2:
    temp = []
    for i1 in l1:
      temp.append(func(i1, i2))
    result.append(temp)

  return result


"""
return the euclidean distance between two points
"""
def distance(point1, point2):
  if len(point1) != len(point2):
    return -1
  distance = 0
  for i in range(len(point1)):
    distance += pow(point1[i] - point2[i], 2)
  return math.sqrt(distance)


"""
Given a point and set of centres,

return the closest point to these centres using euclidean distance
"""
def findBelongingCentrePosition(point, centres):
  assert (len(centres) > 0)
  minDistance = sys.float_info.max
  pos = -1
  for i in range(len(centres)):
    currDistance = distance(point, centres)
    if minDistance > currDistance:
      minDistance = currDistance
      pos = i
  assert pos > -1
  return pos
