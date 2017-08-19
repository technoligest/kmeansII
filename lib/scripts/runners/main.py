import lib.scripts.experiment_plotters as plotter
import lib.scripts.experiment_perfect_matching as hung
import lib.scripts.experiment_readers as reader
import lib.scripts.experiment_utils as utils
import lib.scripts.experiment_serializer as sr

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

def scatterPlotMatchings(e1, e2, func):
  d = utils.adjacencyMatrix(e1.clusters, e2.clusters, func)
  minimum = min([min(x) for x in d])
  if minimum < 0:
    d = [[item - minimum for item in row] for row in d]
  matchings = hung.minimum_weight_perfect_matching(d)
  pairs1 = e1.centres
  pairs2 = [e2.centres[p] for p, _ in matchings]
  plotter.connectedScatterPlot(splitIntoXY(pairs1, pairs2))


expr1id = 234
expr2id = 22
assert (abs(expr2id - expr1id) > 0)
experimentsFile = "../../experiments/Experiment Results/kmeans-DimRedFullDataComplete.txt-test1.txt"
datasetFile = "../../../inputFiles/DimRedFullDataComplete.txt"
experiments = sr.deserialize("../serializedExperiments/kmeans++-DimRedFullDataComplete.txt-test1.txt")
print("Done reading in first thing.")

scatterPlotMatchings(experiments[expr1id], experiments[expr2id],
                     lambda a, b:utils.distance(a.centre, b.centre))
scatterPlotMatchings(experiments[expr1id], experiments[expr2id],
                     lambda l1, l2:-1 * utils.overlap(l1.pointPositions, l2.pointPositions))
k = [sum(i.averageDistancesOverArea) / len(i.averageDistancesOverArea) for i in experiments]
k = [i.distanceToCentres for i in experiments]

plotter.Plotter([k]).comparisonBarPlot()
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
