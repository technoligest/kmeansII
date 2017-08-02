# from experiment_centres import *
import sys
import numpy as np
import experiment_plotters as t
import distance as d
import math
from hungarian import *


def findDistanceMatrix(pointSet1, pointSet2):
  if len(pointSet1) != len(pointSet2):
    return None
  return [[d.findDistance(pointSet1[i],pointSet2[j]) for i in range(len(pointSet2))]for j in range(len(pointSet2))]

"""
Splits pairs into XY
Plotting the result will allow us to view the first element in l1 be matched with first element of l2
And so on.
"""
def splitIntoXY(list1, list2):
  return [[[list1[i][0],list2[i][0]],[list1[i][1],list2[i][1]]] for i in range(len(list1))]

numPoints=25
randomList = [x*100 for x in np.random.rand(numPoints,2)]
randomList2= [x*100 for x in np.random.rand(numPoints,2)]
print("randomList: ")
print(randomList)
print("randomList2: ")
print(randomList2)
t.scatterPlot(splitIntoXY(randomList,randomList2))

matchings = minimum_weight_perfect_matching(findDistanceMatrix(randomList,randomList2))
print(findDistanceMatrix(randomList,randomList2))
print(matchings)

randomList2 = [randomList2[x] for x, y in matchings]


t.scatterPlot(splitIntoXY(randomList,randomList2))

t.plt.show()


# print(minimum_weight_perfect_matching(matrix))




# with open(sys.argv[1]) as file:
#   centres = readCentres(file)
#   plotCentres(centres)
#   plt.show()
  
  
  
  
# plt.figure()
# numSections =10
# plotExperimentRuntimes('../experiments/Experiment Results/kmeans-DimRedFullDataComplete.txt-test1.txt',1,numSections)
# plotExperimentRuntimes('../experiments/Experiment Results/kmeans++-DimRedFullDataComplete.txt-test1.txt',0,numSections)
# plotExperimentRuntimes('../experiments/Experiment Results/kmeans||-DimRedFullDataComplete.txt-test1.txt',-1,numSections)
# plt.show()
