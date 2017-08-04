# from experiment_centres import *

import numpy as np
import experiment_plotters as t
import distance as d
import math
import hungarian as hung
import experiment_readers as exp
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
experimentsFile ="../experiments/Experiment Results/kmeans++-DimRedFullDataComplete.txt-test1.txt"
datasetFile = "../../inputFiles/DimRedFullDataComplete.txt"
experiments = exp.readExperiments(experimentsFile,datasetFile)
dataset = exp.readTwoDFile(datasetFile)
e = ExperimentAnalyzer(experiments,dataset)