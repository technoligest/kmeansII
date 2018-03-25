import lib.scripts.experiment_plotters as plotter
import lib.scripts.experiment_analyzer as an
import lib.scripts.experiment_io as reader
import lib.scripts.experiment_utils as utils
import lib.scripts.experiment_serializer as sr
from lib.scripts.experiment_cluster import Cluster
from lib.scripts.experiment_perfect_matching import minimum_weight_perfect_matching,maximum_weight_perfect_matching
import matplotlib.pyplot as plt
import numpy as np
import sys

def perfectMatch():
  f1 = "/Users/yaseralkayale/Documents/classes/current/honours/kmeansII/lib/scripts/new results/expr0-kmeans++.txt"
  f2 = "/Users/yaseralkayale/Documents/classes/current/honours/kmeansII/lib/scripts/new results/expr2-kmeans++.txt"
  centres1 = np.loadtxt(f1, delimiter=",")
  centres2 = np.loadtxt(f2, delimiter=",")

  distances = utils.adjacencyMatrix(centres1,centres2,lambda p1,p2: utils.distance(p1,p2));

  matching = minimum_weight_perfect_matching(distances);

  plt.figure();
  for i in matching:
    print(centres1[i[0]]);
    print(centres2[i[1]]);
    x,y = utils.splitIntoXY([centres2[i[0]],centres1[i[1]]])
    plt.plot(x,y,marker='o', fillstyle='full', markeredgewidth=0)


"""
returns an array of arrays corresponding to the point positions of every centre
in the experiment run. These pointpositions are disjoint and are calculated based
on the closest points to each centre.
"""
def calcPointPositions(dataset,centres):
  result = [[] for _ in range(len(centres))]
  for instId in range(len(dataset)):
    currCandidateCentreId = 0
    minDistance = sys.float_info.max
    for centreId in range(len(centres)):
      currDistance = utils.distance(dataset[instId], centres[centreId])
      if minDistance > currDistance:
        minDistance = currDistance
        currCandidateCentreId = centreId
    result[currCandidateCentreId].append(instId)
  return result

def perfectMatchFigure():
  f1 = "/Users/yaseralkayale/Documents/classes/current/honours/kmeansII/lib/scripts/new results/expr0-kmeans++.txt"
  f2 = "/Users/yaseralkayale/Documents/classes/current/honours/kmeansII/lib/scripts/new results/expr2-kmeans++.txt"
  centres1 = np.loadtxt(f1, delimiter=",")
  centres2 = np.loadtxt(f2, delimiter=",")
  plt.figure();
  x,y = utils.splitIntoXY(centres1)
  plt.scatter(x,y,marker="o")
  x,y = utils.splitIntoXY(centres2)
  plt.scatter(x,y,marker="o")
  dataset = np.loadtxt("/Users/yaseralkayale/Documents/classes/current/honours/kmeansII/inputFiles/DimRedFullDataComplete.txt")
  pos1 = calcPointPositions(dataset,centres1)
  pos2 = calcPointPositions(dataset,centres2)

  distances = utils.adjacencyMatrix(pos1,pos2,lambda p1,p2: utils.overlap(p1,p2));

  matching = maximum_weight_perfect_matching(distances);

  plt.figure();
  for i in matching:
    print(centres1[i[0]]);
    print(centres2[i[1]]);
    x,y = utils.splitIntoXY([centres2[i[0]],centres1[i[1]]])
    plt.plot(x,y,marker='o', fillstyle='full', markeredgewidth=0)


#
# l = sr.deserialize("/Users/yaseralkayale/Documents/classes/current/honours/kmeansII/lib/scripts/script results/ExperimentsSerialized2017-09-10 21:21:40.108691")
# dataset = np.loadtxt("/Users/yaseralkayale/Documents/classes/current/honours/kmeansII/inputFiles/DimRedFullData.txt")
# analyzer = an.Analyzer(l, dataset);
#
# matchings = analyzer.calcMatchings();
# np.sav
# print(len(matchings))
# dataset = np.loadtxt("/Users/yaseralkayale/Documents/classes/current/honours/kmeansII/inputFiles/DimRedFullDataComplete.txt")
# np.savetxt("/Users/yaseralkayale/Documents/classes/current/honours/kmeansII/inputFiles/DimRedFullDataComplete.csv",dataset,delimiter=",")

perfectMatchFigure();
perfectMatch();
plt.show()

