

import lib.scripts.experiment_serializer as sr
import lib.scripts.experiment_io as reader
import numpy as np

import datetime
def serializeExperiments():
  res = []
  i = 3
  for _ in range(4):
    algos = dict()
    algos["Kmeans"] = None
    algos["Kmeans++"] = None
    algos["Kmeans||"] = None
    for _ in range(3):
      fileName = "../script results/expr" + str(i) + ".txt"
      with open(fileName) as f:
        f.readline()
        k = float(f.readline().strip().split("=")[1])
        l = float(f.readline().strip().split("=")[1])
        r = float(f.readline().strip().split("=")[1])
      exps = reader.readExperiments(fileName, dataset, maxExperiments=5000,debug=True)
      print(len(exps))
      res.append((exps,k,l,r))
      i+=1
    sr.serialize("../script results/ExperimentsSerialized"+str(datetime.datetime.now()), res)
    res.clear()
datasetFile = "../../../inputFiles/DimRed10000.txt"
dataset = np.loadtxt(datasetFile).tolist()


import lib.scripts.experiment_analyzer as an

serializedFiles = ["/home/technoligest/Documents/kmeansNew/kmeansII/lib/scripts/script results/ExperimentsSerialized2017-09-10 21:21:40.108691",
                   "/home/technoligest/Documents/kmeansNew/kmeansII/lib/scripts/script results/ExperimentsSerialized2017-09-10 22:59:44.036064",
                   "/home/technoligest/Documents/kmeansNew/kmeansII/lib/scripts/script results/ExperimentsSerialized2017-09-10 23:34:49.742772",
                   "/home/technoligest/Documents/kmeansNew/kmeansII/lib/scripts/script results/ExperimentsSerialized2017-09-10 23:49:48.436825",
                   "/home/technoligest/Documents/kmeansNew/kmeansII/lib/scripts/script results/ExperimentsSerialized2017-09-11 00:11:54.244566",
                   "/home/technoligest/Documents/kmeansNew/kmeansII/lib/scripts/script results/ExperimentsSerialized2017-09-11 00:41:09.245899"
                   ]

results=[]
for fileNum in range(1,6):
  r = sr.deserialize(serializedFiles[fileNum])
  print("file: ",fileNum)
  for p in r:
    print(p[1:])
  # for rerunNum in range(3):
  #   print("Started fileNum ",fileNum, " rerunNum: ",rerunNum)
  #   a = an.Analyzer(r[rerunNum][0],dataset)
  #   results.append((fileNum,rerunNum,a.cliques()))
  #   print("Just added: ",results[-1])
"""
Results: ran on Oct 14
(1, 0, [13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13])
(1, 1, [13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13])
(1, 2, [13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13])
(2, 0, [25, 20, 22, 21, 18, 18, 14, 14, 13, 16, 12, 11, 14, 12, 11, 11, 12, 13, 10, 11, 10, 10, 10, 10])
(2, 1, [25, 21, 18, 18, 20, 18, 18, 18, 17, 13, 13, 13, 13, 11, 11, 11, 10, 9, 10, 9, 11, 9, 9, 9])
(2, 2, [25, 21, 23, 22, 18, 21, 21, 22, 20, 18, 18, 18, 17, 17, 17, 17, 16, 14, 14, 18, 13, 13, 13, 13])
(3, 0, [50, 38, 37, 31, 25, 20, 19, 22, 15, 15, 12, 13, 10, 6, 9, 7, 6, 7, 5, 7, 7, 6, 6, 5, 5, 5, 5, 4, 6, 3, 4, 4, 3, 3, 3, 3, 4, 5, 4, 5, 4, 3, 4, 3, 4, 3, 4, 3, 3])
(3, 1, [50, 35, 29, 26, 25, 13, 22, 14, 11, 8, 13, 7, 9, 7, 8, 8, 5, 10, 7, 6, 6, 6, 8, 5, 6, 3, 4, 3, 3, 5, 4, 3, 3, 4, 4, 2, 2, 2, 2, 2, 2, 2, 3, 2, 2, 2, 2, 2, 2])
(3, 2, [50, 36, 37, 31, 28, 29, 22, 19, 20, 16, 21, 10, 14, 13, 13, 11, 11, 9, 10, 12, 10, 9, 12, 7, 12, 7, 9, 7, 6, 8, 7, 5, 7, 7, 7, 4, 8, 6, 3, 4, 4, 5, 4, 3, 4, 4, 3, 3, 3])
(4, 0, [75, 55, 45, 33, 25, 20, 23, 24, 17, 15, 13, 19, 14, 14, 8, 10, 7, 8, 11, 10, 6, 4, 9, 5, 5, 6, 3, 6, 5, 5, 9, 5, 4, 2, 4, 4, 3, 5, 5, 3, 5, 3, 2, 4, 4, 3, 2, 3, 2, 3, 2, 2, 2, 3, 2, 2, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2])
(4, 1, [75, 57, 41, 33, 25, 13, 18, 13, 15, 13, 14, 9, 9, 9, 9, 7, 6, 6, 7, 5, 3, 2, 3, 4, 1, 5, 3, 2, 2, 1, 2, 1, 2, 3, 3, 1, 3, 1, 1, 2, 1, 1, 2, 2, 1, 2, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0])
(4, 2, [75, 59, 51, 39, 31, 21, 27, 25, 13, 18, 16, 15, 16, 11, 12, 10, 14, 13, 11, 7, 9, 8, 10, 7, 8, 5, 7, 11, 6, 8, 7, 6, 4, 6, 8, 5, 6, 7, 6, 7, 5, 5, 5, 5, 5, 4, 6, 5, 5, 4, 5, 3, 4, 5, 4, 3, 4, 4, 4, 3, 4, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3])
(5, 0, [100, 65, 49, 33, 25, 22, 18, 12, 18, 9, 18, 16, 13, 8, 8, 9, 7, 3, 7, 5, 5, 4, 4, 5, 1, 1, 3, 5, 3, 2, 3, 3, 1, 2, 3, 2, 2, 3, 0, 2, 2, 2, 1, 3, 1, 3, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0])
(5, 1, [100, 62, 56, 36, 28, 31, 24, 18, 13, 16, 8, 11, 7, 9, 9, 6, 12, 7, 4, 2, 4, 3, 4, 3, 4, 3, 2, 2, 2, 4, 4, 1, 2, 3, 5, 2, 1, 1, 1, 0, 1, 1, 1, 2, 1, 0, 0, 2, 1, 1, 0, 2, 0, 1, 1, 0, 1, 0, 1, 1, 1, 2, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0])
(5, 2, [100, 71, 60, 44, 24, 19, 16, 26, 15, 16, 11, 15, 9, 13, 10, 11, 7, 6, 4, 7, 6, 3, 3, 3, 4, 3, 3, 2, 1, 3, 1, 3, 2, 3, 2, 2, 3, 2, 2, 2, 2, 1, 0, 1, 1, 1, 2, 2, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0])

file:  1
(13.0, 0.5, 8.0)
(13.0, 1.0, 8.0)
(13.0, 2.0, 8.0)
file:  2
(25.0, 0.5, 8.0)
(25.0, 1.0, 8.0)
(25.0, 2.0, 8.0)
file:  3
(50.0, 0.5, 8.0)
(50.0, 1.0, 8.0)
(50.0, 2.0, 8.0)
file:  4
(75.0, 0.5, 8.0)
(75.0, 1.0, 8.0)
(75.0, 2.0, 8.0)
file:  5
(100.0, 0.5, 8.0)
(100.0, 1.0, 8.0)
(100.0, 2.0, 8.0)

"""
#
#
# r = sr.deserialize(serializedFiles[fileNumber])
# print("Len r: ", len(r))
# print("len r[0]: ", len(r[0]))
# for i in range(len(r)):
#   print("r[",i,"]: ", r[i][1:])
# print("len r[0][0]", len(r[0][0]))
#
#
#
#
# experiments = r[rerunNumber][0]
# a = an.Analyzer(experiments,dataset)
# print("The cliques: ")
# # print(a.cliques())
#
# print(a.calcMatchings())
# print(a.matchings)
# # import numpy as np
# # i = np.random.random(5)*500
# # print(i)