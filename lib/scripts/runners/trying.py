#
#
# import lib.scripts.experiment_serializer as sr
# import lib.scripts.experiment_io as reader
# import numpy as np
#
# import datetime
# def serializeExperiments():
#   res = []
#   i = 3
#   for _ in range(4):
#     algos = dict()
#     algos["Kmeans"] = None
#     algos["Kmeans++"] = None
#     algos["Kmeans||"] = None
#     for _ in range(3):
#       fileName = "../script results/expr" + str(i) + ".txt"
#       with open(fileName) as f:
#         f.readline()
#         k = float(f.readline().strip().split("=")[1])
#         l = float(f.readline().strip().split("=")[1])
#         r = float(f.readline().strip().split("=")[1])
#       exps = reader.readExperiments(fileName, dataset, maxExperiments=5000,debug=True)
#       print(len(exps))
#       res.append((exps,k,l,r))
#       i+=1
#     sr.serialize("../script results/ExperimentsSerialized"+str(datetime.datetime.now()), res)
#     res.clear()
# datasetFile = "../../../inputFiles/DimRed10000.txt"
# dataset = np.loadtxt(datasetFile).tolist()
#
#
# import lib.scripts.experiment_analyzer as an
#
# serializedFiles = ["/home/technoligest/Documents/kmeansNew/kmeansII/lib/scripts/script results/ExperimentsSerialized2017-09-10 21:21:40.108691",
#                    "/home/technoligest/Documents/kmeansNew/kmeansII/lib/scripts/script results/ExperimentsSerialized2017-09-10 22:59:44.036064",
#                    "/home/technoligest/Documents/kmeansNew/kmeansII/lib/scripts/script results/ExperimentsSerialized2017-09-10 23:34:49.742772",
#                    "/home/technoligest/Documents/kmeansNew/kmeansII/lib/scripts/script results/ExperimentsSerialized2017-09-10 23:49:48.436825",
#                    "/home/technoligest/Documents/kmeansNew/kmeansII/lib/scripts/script results/ExperimentsSerialized2017-09-11 00:11:54.244566",
#                    "/home/technoligest/Documents/kmeansNew/kmeansII/lib/scripts/script results/ExperimentsSerialized2017-09-11 00:41:09.245899"
#                    ]
#
# results=[]
# for fileNum in range(1,6):
#   r = sr.deserialize(serializedFiles[fileNum])
#   print("file: ",fileNum)
#   for p in r:
#     print(p[1:])
#   # for rerunNum in range(3):
#   #   print("Started fileNum ",fileNum, " rerunNum: ",rerunNum)
#   #   a = an.Analyzer(r[rerunNum][0],dataset)
#   #   results.append((fileNum,rerunNum,a.cliques()))
#   #   print("Just added: ",results[-1])
# """
# Results: ran on Oct 14
# (1, 0, [13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13])
# (1, 1, [13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13])
# (1, 2, [13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13])
# (2, 0, [25, 20, 22, 21, 18, 18, 14, 14, 13, 16, 12, 11, 14, 12, 11, 11, 12, 13, 10, 11, 10, 10, 10, 10])
# (2, 1, [25, 21, 18, 18, 20, 18, 18, 18, 17, 13, 13, 13, 13, 11, 11, 11, 10, 9, 10, 9, 11, 9, 9, 9])
# (2, 2, [25, 21, 23, 22, 18, 21, 21, 22, 20, 18, 18, 18, 17, 17, 17, 17, 16, 14, 14, 18, 13, 13, 13, 13])
# (3, 0, [50, 38, 37, 31, 25, 20, 19, 22, 15, 15, 12, 13, 10, 6, 9, 7, 6, 7, 5, 7, 7, 6, 6, 5, 5, 5, 5, 4, 6, 3, 4, 4, 3, 3, 3, 3, 4, 5, 4, 5, 4, 3, 4, 3, 4, 3, 4, 3, 3])
# (3, 1, [50, 35, 29, 26, 25, 13, 22, 14, 11, 8, 13, 7, 9, 7, 8, 8, 5, 10, 7, 6, 6, 6, 8, 5, 6, 3, 4, 3, 3, 5, 4, 3, 3, 4, 4, 2, 2, 2, 2, 2, 2, 2, 3, 2, 2, 2, 2, 2, 2])
# (3, 2, [50, 36, 37, 31, 28, 29, 22, 19, 20, 16, 21, 10, 14, 13, 13, 11, 11, 9, 10, 12, 10, 9, 12, 7, 12, 7, 9, 7, 6, 8, 7, 5, 7, 7, 7, 4, 8, 6, 3, 4, 4, 5, 4, 3, 4, 4, 3, 3, 3])
# (4, 0, [75, 55, 45, 33, 25, 20, 23, 24, 17, 15, 13, 19, 14, 14, 8, 10, 7, 8, 11, 10, 6, 4, 9, 5, 5, 6, 3, 6, 5, 5, 9, 5, 4, 2, 4, 4, 3, 5, 5, 3, 5, 3, 2, 4, 4, 3, 2, 3, 2, 3, 2, 2, 2, 3, 2, 2, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2])
# (4, 1, [75, 57, 41, 33, 25, 13, 18, 13, 15, 13, 14, 9, 9, 9, 9, 7, 6, 6, 7, 5, 3, 2, 3, 4, 1, 5, 3, 2, 2, 1, 2, 1, 2, 3, 3, 1, 3, 1, 1, 2, 1, 1, 2, 2, 1, 2, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0])
# (4, 2, [75, 59, 51, 39, 31, 21, 27, 25, 13, 18, 16, 15, 16, 11, 12, 10, 14, 13, 11, 7, 9, 8, 10, 7, 8, 5, 7, 11, 6, 8, 7, 6, 4, 6, 8, 5, 6, 7, 6, 7, 5, 5, 5, 5, 5, 4, 6, 5, 5, 4, 5, 3, 4, 5, 4, 3, 4, 4, 4, 3, 4, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3])
# (5, 0, [100, 65, 49, 33, 25, 22, 18, 12, 18, 9, 18, 16, 13, 8, 8, 9, 7, 3, 7, 5, 5, 4, 4, 5, 1, 1, 3, 5, 3, 2, 3, 3, 1, 2, 3, 2, 2, 3, 0, 2, 2, 2, 1, 3, 1, 3, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0])
# (5, 1, [100, 62, 56, 36, 28, 31, 24, 18, 13, 16, 8, 11, 7, 9, 9, 6, 12, 7, 4, 2, 4, 3, 4, 3, 4, 3, 2, 2, 2, 4, 4, 1, 2, 3, 5, 2, 1, 1, 1, 0, 1, 1, 1, 2, 1, 0, 0, 2, 1, 1, 0, 2, 0, 1, 1, 0, 1, 0, 1, 1, 1, 2, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0])
# (5, 2, [100, 71, 60, 44, 24, 19, 16, 26, 15, 16, 11, 15, 9, 13, 10, 11, 7, 6, 4, 7, 6, 3, 3, 3, 4, 3, 3, 2, 1, 3, 1, 3, 2, 3, 2, 2, 3, 2, 2, 2, 2, 1, 0, 1, 1, 1, 2, 2, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0])
#
# file:  1
# (13.0, 0.5, 8.0)
# (13.0, 1.0, 8.0)
# (13.0, 2.0, 8.0)
# file:  2
# (25.0, 0.5, 8.0)
# (25.0, 1.0, 8.0)
# (25.0, 2.0, 8.0)
# file:  3
# (50.0, 0.5, 8.0)
# (50.0, 1.0, 8.0)
# (50.0, 2.0, 8.0)
# file:  4
# (75.0, 0.5, 8.0)
# (75.0, 1.0, 8.0)
# (75.0, 2.0, 8.0)
# file:  5
# (100.0, 0.5, 8.0)
# (100.0, 1.0, 8.0)
# (100.0, 2.0, 8.0)
#
# """
# #
# #
# # r = sr.deserialize(serializedFiles[fileNumber])
# # print("Len r: ", len(r))
# # print("len r[0]: ", len(r[0]))
# # for i in range(len(r)):
# #   print("r[",i,"]: ", r[i][1:])
# # print("len r[0][0]", len(r[0][0]))
# #
# #
# #
# #
# # experiments = r[rerunNumber][0]
# # a = an.Analyzer(experiments,dataset)
# # print("The cliques: ")
# # # print(a.cliques())
# #
# # print(a.calcMatchings())
# # print(a.matchings)
# # # import numpy as np
# <<<<<<< HEAD
# # # i = np.random.random(5)*500
# # # print(i)
# =======
# # # import matplotlib.pyplot as plt
# #
# #
# # # N = 5
# # # menMeans = (20, 35, 30, 35, 27)
# # # womenMeans = (25, 32, 34, 20, 25)
# # # womennMeans = (25, 32, 34, 20, 25)
# # # width = 10       # the width of the bars: can also be len(x) sequence
# # # ind = [i*20 for i in np.arange(N)]    # the x locations for the groups
# # #
# # # # p1 = plt.bar(ind, menMeans, width, color='#d62728',)
# # # # p2 = plt.bar(ind, womenMeans, width, bottom=menMeans)
# # #
# # # p1 = plt.bar(ind, menMeans, width, color='#d62728')
# # # p2 = plt.bar(ind, womenMeans, width, menMeans)
# # #
# # # plt.ylabel('Scores')
# # # plt.title('Scores by group and gender')
# # # plt.xticks(ind, ('G1', 'G2', 'G3', 'G4', 'G5'))
# # # plt.yticks(np.arange(-10, 81, 5))
# # #
# # # plt.legend((p1[0], p2[0]), ('Men', 'Women'))
# # #
# # # plt.show()
# # # rn.plt.show()
# #
# #
# #
# # """
# #
#
# # import lib.scripts.experiment_serializer as ser
# # import lib.scripts.experiment_plotters as plt
# # import numpy as np
# # import lib.scripts.experiment_convex_hull as hull
# # import random as rand
# # import lib.scripts.experiment_io as reader
# # print(rand.random())
# # def decreaseDatasetSize():
# #   datasetFile = "../../../inputFiles/DimRedFullDataComplete.txt"
# #   with open(datasetFile) as file:
# #     dataset = reader.readTwoDFile(file)
# #   result=[]
# #   for i in range(10000):
# #     result.append(dataset[rand.random()*len(dataset)])
# #   return result
# #
# #
# # import lib.scripts.experiment_utils as utils
# # import numpy as np
# #
# # datasetFile = "../../../inputFiles/DimRedFullDataComplete.txt"
# # with open(datasetFile) as file:
# #   dataset = reader.readTwoDFile(file)
# #
# # i = utils.splitIntoXY(dataset[:20000])
# # x = np.array(i[0])
# # y = np.array(i[1])
# # plt.plotHeetMap(x,y)
# # plt.show()
#
#
#
# # def listToString(l):
# #   result = ""
# #   for i in l:
# #     result += str(i)
# #   return result
# # il = dict()
# # k = [1, 2, 3, 4, 5, 5]
# # z = [1, 2, 3, 4, 5, 5]
# # il[str(k)] = 17
# # il[str(z)] = 20
# # print(il)
#
#
# import lib.scripts.experiment_serializer as sr
# import lib.scripts.experiment_io as reader
# import numpy as np
# import lib.scripts.experiment_convex_hull as cv
# import matplotlib.pyplot as plt
# import lib.scripts.experiment_cluster as cl
# import time
# import lib.scripts.experiment_utils as utils
# import lib.scripts.strongly_connected_componenents as scc
# import lib.scripts.experiment_plotters as pl
# # experiments = sr.deserialize("../serializedExperiments/NewExperimentskmeans||.txt")
# # with open(datasetFile) as file:
# #   cl.Cluster.dataset = reader.readTwoDFile(file)
# #
# # mat = utils.adjacencyMatrix(experiments[0].clusters,experiments[1].clusters,lambda a, b:bin(a.binaryPointPositions & b.binaryPointPositions).count("1") - 1)
# # mat2 = utils.fastAdjacencyMatrix(experiments[0].clusters,experiments[1].clusters)
# #
# # assert(len(mat)==len(mat2))
# #
# # for i in range(len(mat)):
# #   print(mat[i])
# #   print(mat2[i])
# #   print()
#
#
# datasetFile = "../../../inputFiles/DimRed10000.txt"
# dataset = np.loadtxt(datasetFile).tolist()
# # print(dataset)
# #
# # pl.plotCentres(cv.calcConvexHull(dataset))
# # pl.plotCentres(dataset)
# # pl.show()
# # exps = reader.readExperiments("../script results/expr0.txt", dataset, maxExperiments=450)
# # print("#Iterations")
# # print("algorithm\tmin\tavg\tmax")
# # print(exps[0].numIterations, "\t", )
# # for i in exps:
# #   print(i)
# #
# import datetime
# def serializeExperiments():
#   res = []
#   i = 0
#   for _ in range(5):
#     algos = dict()
#     algos["Kmeans"] = None
#     algos["Kmeans++"] = None
#     algos["Kmeans||"] = None
#     for _ in range(3):
#       fileName = "../script results/expr" + str(i) + ".txt"
#       with open(fileName) as f:
#         f.readline()
#         k = float(f.readline().strip().split("=")[1])
#         l = float(f.readline().strip().split("=")[1])
#         r = float(f.readline().strip().split("=")[1])
#       exps = reader.readExperiments(fileName, dataset, maxExperiments=500)
#       res.append((exps,k,l,r))
#     sr.serialize("../script results/ExperimentsSerialized"+str(datetime.datetime.now()), res)
#     res.clear()
# serializeExperiments()
# # i = 0
# # previousK = -1
# # for _ in range(5):
# #   algos = dict()
# #   algos["Kmeans"] = None
# #   algos["Kmeans++"] = None
# #   algos["Kmeans||"] = None
# #   for _ in range(3):
# #     fileName = "../script results/expr" + str(i) + ".txt"
# #     with open(fileName) as f:
# #       f.readline()
# #       k = float(f.readline().strip().split("=")[1])
# #       l = float(f.readline().strip().split("=")[1])
# #       r = float(f.readline().strip().split("=")[1])
# #     exps = reader.readExperiments(fileName, dataset, maxExperiments=500)
# #     for key in algos:
# #       algos[key] = [i.numIterations for i in exps if i.algorithm.strip() == key]
# #     if k != previousK:
# #       # tab.header(["algorithm","min","avg","max"])
# #       print("K val: ", k)
# #       print("algorithm\t\t\t\t\tmin\t\t\tavg\t\t\tmax")
# #       previousK = k
# #     for key in algos:
# #       t = algos[key]
# #       if len(t) == 0:
# #         continue
# #       if key == "Kmeans||":
# #         key += "(l=" + str(l) + ",r=" + str(r) + ")"
# #       # tab.add_row((key, min(t), sum(t) / len(t), max(t)))
# #       print(key,"\t\t\t\t\t", min(t),"\t\t\t", sum(t) / len(t),"\t\t\t", max(t))
# #     if k != previousK:
# #       # print(tab.draw)
# #       print()
# #       print()
# #     i += 1
# #
#
#
#
# expr1id = 0
# expr2id = 1
# assert (abs(expr2id - expr1id) > 0)
# datasetFile = "../../../inputFiles/DimRedFullDataComplete.txt"
# with open(datasetFile) as file:
#   dataset = reader.readTwoDFile(file)
# # Cluster.dataset=cluster
# experiments = sorted(sr.deserialize("../serializedExperiments/NewExperimentskmeans||.txt"),key=lambda exp:exp.distanceToCentres)
# print("Done reading in first thing.")
#
# # plotter.scatterPlotMatchings(experiments[expr1id], experiments[expr2id],
# #                      lambda a, b:utils.distance(a.centre, b.centre))
# # plotter.scatterPlotMatchings(experiments[expr1id], experiments[expr2id],
# #                      lambda l1, l2:-1 * utils.overlap(l1.pointPositions, l2.pointPositions))
# #
# # k = [sum(i.averageDistancesOverArea) / len(i.averageDistancesOverArea) for i in experiments]
# # k = [i.distanceToCentres for i in experiments]
# numExperiments = 150
# analyzer = an.Analyzer(experiments[:numExperiments], dataset)
# # analyzer.matchings = sr.deserialize("Matchings for 100.txt")
# analyzer.matchings = sr.deserialize("Matching for 1000kmeans||.txt")
# import sys
# sys.setrecursionlimit(10000000)
# y=[]
# x=[]
# for k in range(numExperiments):
#   print(k, " finished.")
#   y.append(analyzer.calcClique([i for i in range(k)]))
#   x.append(k)
# plotter.connectedScatterPlot([[x,y]])
# # print(analyzer.calcNorbertClique([0,1]))
# # print(analyzer.NIDs)
#
# # k = analyzer.totalDistanceToCentres
#
# # plotter.Plotter([k], xlabel="Total Distance To Centres", ylabel="Number of Experiments/total number of oxperiments",
# #                 plotName="Objective Function Comparison").comparisonBarPlot()
#
# plotter.plt.show()
#
# """
# minimum weight perfect matching in terms of:
# euclidean distance in terms of clusterCentres
# max weight # common points
# max weight intersection/union
#
#
# find:
# average (intersection/union)
# (total # correctly classidied points/#points)-
#
# Google: Ways to compare k-means results/clustering results (Email Vlado)
#
# Meeting with vlado (Tuesday and Wednesday Afternoon)
#
# """
#

#
# ks = [10, 25, 50, 100]
# for k in ks:
#   print(("{0:4d}").format(k));
# print(("{0:4s}|{1:^47s}|{2:^47s}|{3:^47s}" ).format("","Average Func","Min Func","Average Time"))
# print(("{0:4s}|{1:^15s}|{2:^15s}|{3:^15s}|{4:^15s}|{5:^15s}|{6:^15s}|{7:^15s}|{8:^15s}|{9:^15s}" ).format("k","Kmeans","Kmeans++","KmeansNew","Kmeans","Kmeans++","KmeansNew","Kmeans","Kmeans++","KmeansNew"))
#
#


a,b = c = (5,6)

print("a: ",a)
print("b: ",b)
print("c: ",c)