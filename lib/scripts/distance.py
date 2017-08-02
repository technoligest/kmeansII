import math

def findDistance(point1, point2):
  if len(point1)!=len(point2):
    return -1
  distance = 0
  for i in range(len(point1)):
    distance+= pow(point1[i]-point2[i],2)
  return math.sqrt(distance)