import subprocess
import datetime
import os.path
import lib.scripts.experiment_utils as utils
import numpy as np
import time


executableName = "/Users/yaseralkayale/Documents/classes/current/honours/kmeansII/cmake-build-debug/kmeans2"
"""
Runs the algorithm 
"""
def runExperiment(executableName, k, inputFileName, outputFileName, algorithm, l=None, r=None):
  if (algorithm == "kmeansII" or algorithm == "kmeansNew"):
    assert (l != None and r != None)
    p = subprocess.run(
      [executableName, "-i", inputFileName, "-k", str(k), "-a", algorithm, "-o", outputFileName, "-l", str(l), "-r",
       str(r)])
  else:
    p = subprocess.run(
      [executableName, "-i", inputFileName, "-k", str(k), "-a", algorithm, "-o", outputFileName])
  if p.returncode != 0:
    exit("Shit went wrong. Check what happened.")


def runFullExperiment():
  n = 20
  ks = [10, 25, 50, 100]
  datasetNames = ["spam"] #["cloud", "spam", "kddcup"]
  datasetsLocation = "/Users/yaseralkayale/Documents/classes/current/honours/kmeansII/finalDatasets/"
  algorithms = ["kmeansNew"] #["kmeans","kmeans++,"kmeansNew"]
  outLocation = "/Users/yaseralkayale/Documents/classes/current/honours/kmeansII/lib/scripts/new results/"
  for datasetName in datasetNames:
    print("Started: " + datasetName);
    i = 0;
    for k in ks:
      for _ in range(n):
        for algo in algorithms:
          runExperiment(executableName=executableName, k=k, inputFileName=datasetsLocation + datasetName,
                        outputFileName=outLocation + datasetName + "/" + algo + "-out" + str(i), algorithm=algo, l=5,
                        r=5);
        i += 1
        print("finished: " + str(i))
import re
def readFile(file):
  iteration = 0
  inputFile = ""
  seeding = 0
  distance = 0
  for line in file:
    it_reg = re.search('(?<=Input:).*', line)
    if (it_reg != None):
      inputFile = it_reg.group(0)
    it_reg = re.search('(?<=Iterations time:).*', line)
    if (it_reg != None):
      iteration = float(it_reg.group(0));
    it_reg = re.search('(?<=Seeding tim:).*', line)
    if (it_reg != None):
      seeding = float(it_reg.group(0));
    it_reg = re.search('(?<=Distance squared:).*', line)
    if (it_reg != None):
      distance = float(it_reg.group(0));
  return inputFile, iteration, seeding, distance;

def numfile(filename):
  with open(filename) as f:
    for i, l in enumerate(f):
      pass
  return i + 1
def analyze():
  ks = [10, 25, 50, 100]
  datasetNames = ["cloud", "spam", "kddcup"]
  algorithms = ["kmeans", "kmeans++", "kmeansNew"]



  class run:
    def __init__(self, inputFile, iterationTime, seedingTime, distance, k, algo, datasetName):
      self.inputFile = inputFile
      self.iterationTime = iterationTime
      self.seedingTime = seedingTime
      self.distance = distance
      self.k = k
      self.algorithm = algo
      self.datasetName = datasetName
    def __repr__(self):
      return (
            "inputFile:" + self.inputFile +
            "\niterationsTime: " + str(self.iterationTime) +
            "\nseedingTime: " + str(self.seedingTime) +
            "\ndistance: " + str(self.distance) +
            "\nk: " + str(self.k) +
            "\nalgorithm: " + self.algorithm +
            "\ndatasetName: " + self.datasetName)
  runs = []
  datasetNames = ["kddcup"]  # ["cloud", "spam", "kddcup"]
  root = "/Users/yaseralkayale/Documents/classes/current/honours/kmeansII/lib/scripts/new results/";
  for datasetName in datasetNames:
    for i in range(40):
      for algo in algorithms:
        file = open(root + datasetName + "/" + algo + "-out" + str(i) + ".extra")
        res = readFile(file);
        (inputFile, iterationTime, seedingTime, distance), k = res, numfile(
          root + datasetName + "/" + algo + "-out" + str(i))
        r = run(inputFile, iterationTime, seedingTime, distance, k, algo, datasetName)
        runs.append(r)

  distances = dict()
  runningTimes = dict()
  for algo in algorithms:
    distances[algo] = [r.distance for r in runs if r.algorithm == algo and r.k == 10]
    # runningTimes[algo] = [r.seedingTime+r.iterationTime for r in runs if r.algorithm == algo]

  for algo in algorithms:
    print("Average over " + str(len(distances[algo])) + " runs for " + algo + ": " + str(
      sum(distances[algo]) / len(distances[algo])))
  for algo in algorithms:
    print("Minimum over " + str(len(distances[algo])) + " runs for " + algo + ": " + str(
      min(distances[algo])))

def main():
  runExperiment(executableName, 50,
                "/Users/yaseralkayale/Documents/classes/current/honours/kmeansII/finalDatasets/spam",
                "/Users/yaseralkayale/Documents/classes/current/honours/kmeansII/lib/scripts/runners", "kmeansNew", 10,
                10)
  pass;
# main()
# runFullExperiment();
analyze()


225511000000000.0
1110370000000000.0
1054790000000000.0