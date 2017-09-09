import subprocess
import datetime
import os.path
import lib.scripts.experiment_utils as utils
import numpy as np
import time

"""
given a dataset, return a reduced dataset to the given newSize
"""
def reduceDataset(dataset, newSize):
  if newSize > len(dataset):
    return None
  result = []
  for _ in range(newSize):
    result.append(dataset[int(np.random.rand()*len(dataset))])
  return np.array(result)

"""
ks is the values of k to run
ls is the values of l to run
r is the number of rounds for kmeans||
"""
def runExperiments(ks,ls,r,numExperiments,inputFileName,executableName):
  i = 0
  for k in ks:
    for l in ls:
      start = time.time()
      outPutFileName = "/Users/yaseralkayale/Documents/classes/kmeansII/lib/scripts/script results/expr" + str(i) + ".txt"
      while os.path.isfile(outPutFileName):
        i += 1
        outPutFileName = "/Users/yaseralkayale/Documents/classes/kmeansII/lib/scripts/script results/expr" + str(
          i) + ".txt"
      p = subprocess.run(
        [executableName, "-i", inputFileName, "-k", str(k), "-o", outPutFileName, "-l", str(l * k), "-r", str(r),
         "-numExperiments", str(numExperiments)])
      if p.returncode != 0:
        exit("shit went wrong")
      toAppend = str(datetime.datetime.now()) + "\nk = " + str(k) + "\nl = " + str(l) + "\nr = " + str(r) + "\n\n"
      utils.fileAppend(outPutFileName, toAppend)
      print("expr" + str(i) + " finished in "+str(time.time()-start))
      i += 1

ks = [13, 25, 50, 75, 100] #values of k to be tested.
ls = [0.25, 0.5, 1, 2] #valeus of l to be testd (for kmeans||)
r = 8 #number of rounds for kmeans||
ks=[100]
numExperiments = 1

inputFileName = "../../../inputFiles/DimRed10000.txt"
executableName = "/Users/yaseralkayale/Documents/classes/kmeansII/cmake-build-debug/experiments"

runExperiments(ks,ls,r,numExperiments,inputFileName,executableName)

