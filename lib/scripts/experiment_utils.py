import math
import sys
import functools
import operator as op
import time
"""
n choose r
"""
def ncr(n, r):
  r = min(r, n - r)
  if r == 0: return 1
  numer = functools.reduce(op.mul, range(n, n - r, -1))
  denom = functools.reduce(op.mul, range(1, r + 1))
  return numer // denom







"""
calculate the union of 2 numerical lists
"""
def overlap(l1, l2):
  l1Pos = 0
  l2Pos = 0
  result = 0
  while l1Pos < len(l1) and l2Pos < len(l2):
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


"""
Splits pairs into XY
Plotting the result will allow us to view the first element in l1 be matched with first element of l2
And so on.

Or split data which is of the form [[x1,y1],[x2,y2],....] to [[x1,x2,x3,...],[y1,y2,y3,....]]
"""
def splitIntoXY(list1, list2=None):
  if list2 == None:
    return [[x[0] for x in list1], [x[1] for x in list1]]
  return [[[list1[i][0], list2[i][0]], [list1[i][1], list2[i][1]]] for i in range(len(list1))]


"""
Return the total number of shift for
Two lists. Assuming that the two lists are sorted
so that list1[0] is matched with list2[0] and so on
"""
def totalShiftedDistance(list1, list2):
  result = 0
  assert (len(list1) == len(list2))
  for i in range(len(list1)):
    result += distance(list1[i], list2[i])
  return result


def printRunningTime(func):
  def wrapper(*args):
    print("started: ",func.__name__)
    start = time.time()
    result = func(*args)
    print(func.__name__, " ran in: ", (time.time() - start))
    return result
  return wrapper

"""
given 2 lists and a function. Calculate the adjavency matrix between these two lists
by applying the function on every pair from the two
-basically creating a complete bipartite graph of the 2 sets of points
"""
@printRunningTime
def adjacencyMatrix(l1, l2, func):
  result = []
  for i2 in l2:
    temp = []
    for i1 in l1:
      start =time.time()
      temp.append(func(i1, i2))
    result.append(temp)
  return result

"""
Append a give string to a file with the given file name
"""
def fileAppend(fileName, str):
  l=[]
  with open(fileName) as f:
    for item in f:
      l.append(item)
    f.closed
  with open(fileName,"w+") as f2:
    f2.write(str)
    for item in l:
      f2.write(item)
    f2.closed

"""
Convert a list into its string representation concatenated
"""
def listToString(self, l):
  result = ""
  for i in l:
    result += str(i)
  return result


def fastAdjacencyMatrix(c1,c2):
  assert(len(c1)==len(c2))
  closestCentrePositions = []
  for cluster in c1:
    distances = [distance(cluster.centre,cluster2.centre) for cluster2 in c2]
    distances = [(i,distances[i]) for i in range(len(distances))]
    closestCentrePositions.append(sorted([x for x,y in sorted(distances,key=lambda x: x[1])[:1]]))
  result=[]
  for centre2Index in range(len(c1)):
    row = []
    for centre1Index in range(len(c2)):
      if centre2Index in closestCentrePositions[centre1Index]:
        row.append(overlap(c1[centre1Index].pointPositions,c2[centre2Index].pointPositions))
      else:
        row.append(0)
    result.append(row)
  return result
