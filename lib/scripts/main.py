# from experiment_centres import *

import numpy as np
import experiment_plotters as t
import distance as d
import math
import hungarian as hung
import experiment_readers as exp
from distance import findDistanceMatrix
from experiment_analyzer import ExperimentAnalyzer

"""
Splits pairs into XY
Plotting the result will allow us to view the first element in l1 be matched with first element of l2
And so on.
"""
def splitIntoXY(list1, list2):
    return [[[list1[i][0], list2[i][0]], [list1[i][1], list2[i][1]]] for i in range(len(list1))]


# numPoints = 25
# randomList = [x * 100 for x in np.random.rand(numPoints, 2)]
# randomList2 = [x * 100 for x in np.random.rand(numPoints, 2)]
# print("randomList: ")
# print(randomList)
# print("randomList2: ")
# print(randomList2)
# t.scatterPlot(splitIntoXY(randomList, randomList2))
# distMat =d.findDistanceMatrix(randomList, randomList2)
# print("Distance matrix: ")
# print(len(distMat))
# matchings = hung.minimum_weight_perfect_matching(distMat)
# print(d.findDistanceMatrix(randomList, randomList2))
# print(matchings)
#
# randomList2 = [randomList2[x] for x, y in matchings]
#
# t.scatterPlot(splitIntoXY(randomList, randomList2))
#
# t.plt.show()
#
class HaltException(Exception):pass




expr1id=0
expr2id=1

experimentsFile ="../experiments/Experiment Results/kmeans++-DimRedFullDataComplete.txt-test1.txt"
datasetFile = "../../inputFiles/DimRedFullDataComplete.txt"
experiments = exp.readExperiments(experimentsFile,datasetFile,max(expr1id,expr2id)+1)
dataset = exp.readTwoDFile(datasetFile)
# e = ExperimentAnalyzer(experiments,dataset


d = findDistanceMatrix(experiments[expr1id].centres, experiments[expr2id].centres)
v = hung.minimum_weight_perfect_matching(d)
output = [experiments[expr2id].centres[p] for p,y in v]
t.scatterPlot(splitIntoXY(experiments[expr1id].centres, output))


print("started picking d:")
d = [[-1*len([val for val in i1.pointPositions if val in i2.pointPositions]) for i2 in experiments[expr1id].clusters]for i1 in experiments[expr2id].clusters]
print(d)
# print("calculating initial d is done.")
# minim = min([min(k) for k in d])
# print("finding min is done.")
# k = [[i-minim for i in k]for k in d]
# print("d:")
# for i in k:
#     for j in i:
#         if not j==3184:
#             print(j)
#     print()
# # try:
# v = hung.minimum_weight_perfect_matching(k)
# # except HaltException as h:
# #     print(h)
# print("min weight is done")
# output = [experiments[expr2id].centres[p] for p,y in v]
# t.scatterPlot(splitIntoXY(experiments[expr1id].centres, output))
# t.scatterPlot(dataset)
# t.plt.show()

# main()

"""
minimum weight perfect matching in terms of:
euclidean distance in terms of clusterCentres
max weight # common points
max weight intersection/union


find:
average (intersection/union)
(total # correctly classidied points/#points)-

Google: Ways to compare k-means results/clustering results (Email Vlado)

Meeting with vlado (Tuesday and Wednesday Afternoon)

"""
