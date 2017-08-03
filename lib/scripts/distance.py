import math
import sys



def findDistance(point1, point2):
  if len(point1)!=len(point2):
    return -1
  distance = 0
  for i in range(len(point1)):
    distance+= pow(point1[i]-point2[i],2)
  return math.sqrt(distance)
def findBelongingCentrePosition(point, centres):
  minDistance = sys.float_info.max
  pos = -1
  for i in range (len(centres)):
    currDistance = findDistance(point,centres)
    if minDistance>currDistance
      minDistance=currDistance
      pos=i
  assert po>-1
  return pos

  def findDistanceMatrix(pointSet1, pointSet2):
  if len(pointSet1) != len(pointSet2):
    return None
  return [[findDistance(pointSet1[i],pointSet2[j]) for i in range(len(pointSet2))]for j in range(len(pointSet2))]
