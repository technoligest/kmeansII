import subprocess
import datetime
import sys
import os.path
import lib.scripts.experiment_utils as utils


ks = [13, 25, 50, 75, 100]
ls = [0.1, 0.5, 1, 2]
r = 8
numExperiments = 5
ks = [13, 25, 50, 75, 100]  # to be deleted
ls = [0.25, 0.5, 1, 2]  # to be deleted

inputFileName = "../../../inputFiles/DimRedFullData.txt"
executableName = "/Users/yaseralkayale/Documents/classes/kmeansII/cmake-build-debug/experiments"
i = 0
for k in ks:
  for l in ls:
    outPutFileName = "/Users/yaseralkayale/Documents/classes/kmeansII/lib/scripts/script results/expr" + str(i) + ".txt"
    while os.path.isfile(outPutFileName):
      print("OutPutFileExists. Trying next number.")
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
    print("expr" + str(i) + " finished")
    i += 1
