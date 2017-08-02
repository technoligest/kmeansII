import numpy as np
import math
from distance import *
from experiment_plotters import *
def cosSquaredOfPolarAngle(origin,p1, p2):
    if  p2==origin or p1==origin:
        return -1
    result= (math.degrees(math.acos(((p1[0]-origin[0])*(p2[0]-origin[0])+
                                    (p1[1]-origin[1])*(p2[1]-origin[1])
                                   )/
                                   (findDistance(origin,p1)*
                                    findDistance(origin,p2)
                                   )
                                  )
                        )
           )
    return result
                  
    
def isNotLeftTurn(rightPoint, origin, leftPoint):
    return (0 <= ((origin[1] - rightPoint[1]) * (leftPoint[0] - origin[0]) -
                 (origin[0] - rightPoint[0]) * (leftPoint[1] - origin[1])))
def calcConvexHull(matrix):
    matrix=sorted(matrix, key = lambda l:l[0])
    matrix=sorted(matrix, key = lambda l:l[1])
    lowestRight=[matrix[0][0]+5,matrix[0][1]]
    anglesToLowestPoint = [cosSquaredOfPolarAngle(matrix[0],lowestRight,matrix[id]) for id in range(len(matrix))]
    anglesToLowestPoint[0]=-1
    matrix = [l[0] for l in sorted(zip(matrix,anglesToLowestPoint), key=lambda pair: pair[1])]
    result = [matrix[0],matrix[1],matrix[2]]
    for i in range(3,len(matrix)):
        while isNotLeftTurn(result[len(result)-2],result[len(result)-1],matrix[i]):
            del result[len(result)-1]
        result.append(matrix[i])
    return result
    
"""
Assumes input as the output of the convexHull algorithm
Anything else will give problems
"""
def calcConvexHullArea(convexHull):
    if len(convexHull)<3:
        return 0
    result=0
    for i in range(len(convexHull)-1):
        result+=(convexHull[i][0]*convexHull[i+1][1]-
                 convexHull[i][1]*convexHull[i+1][0])
    result+=(convexHull[len(convexHull)-1][0]*convexHull[0][1]-
             convexHull[len(convexHull)-1][1]*convexHull[0][0])
    return result
v=[list(i) for i in np.random.rand(10000,2)]


scatterPlot([convertToXY(calcConvexHull(v))])
plt.show()
print(calcConvexHullArea(calcConvexHull(v)))

# print(math.degrees(math.acos(1)))