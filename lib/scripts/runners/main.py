import os

dir_path = os.path.dirname(os.path.realpath(__file__))
print(dir_path)

import lib.scripts.experiment_plotters as plotter
import lib.scripts.experiment_perfect_matching as hung
import lib.scripts.experiment_readers as reader
from  lib.scripts.experiment_distances import findDistanceMatrix
import lib.scripts.experiment_utils as utils

"""
Splits pairs into XY
Plotting the result will allow us to view the first element in l1 be matched with first element of l2
And so on.

Or split data which is of the form [[x1,y1],[x2,y2],....] to [[x1,x2,x3,...],[y1,y2,y3,....]]
"""

def splitIntoXY(list1, list2=None):
  if list2 == None:
    return [[x[0] for x in list], [x[1] for x in list]]
  return [[[list1[i][0], list2[i][0]], [list1[i][1], list2[i][1]]] for i in range(len(list1))]

def calcOverlapMatrix(l1, l2):
  result = []
  for i1 in l1:
    temp = []
    for i2 in l2:
      temp.append(utils.overlap(i1.pointPositions, i2.pointPositions))
    result.append(temp)
  return result

# def scatterPlotMatchings(list1,list2, distanceMetric):



expr1id = 3
expr2id = 4

experimentsFile = "../../experiments/Experiment Results/kmeans-DimRedFullDataComplete.txt-test1.txt"
datasetFile = "../../../inputFiles/DimRedFullDataComplete.txt"
experiments, dataset = reader.readExperiments(experimentsFile, datasetFile, max(expr1id, expr2id) + 1)
print("done reading in first thing")
"""
plot in terms of euclidean distance between the points
"""
# scatterPlotMatchings(experiments[expr1id].centres,experiments[expr2id].centres, findDistanceMatrix)
list1=experiments[expr1id].centres
list2=experiments[expr2id].centres
d = findDistanceMatrix(list1, list2)
matchings = hung.minimum_weight_perfect_matching(d)
reorderedList2 = [list2[p] for p, _ in matchings]
plotter.connectedScatterPlot(splitIntoXY(list1, reorderedList2))

print("done potting first thing")
"""
Plot in terms of efficinet overlapping of points
"""
d = calcOverlapMatrix(experiments[expr2id].clusters, experiments[expr1id].clusters)

maximum = max([max(k) for k in d])
d = [[-1 * (item - maximum) for item in row] for row in d]
matchings = hung.minimum_weight_perfect_matching(d)
reorderedExpr2 = [experiments[expr2id].centres[p] for p, _ in matchings]
plotter.connectedScatterPlot(splitIntoXY(experiments[expr1id].centres, reorderedExpr2))
print("done plotting the second thing.")

"""
Show everything
"""
plotter.plt.show()

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
