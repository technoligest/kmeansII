import subprocess
import re
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
  datasetNames = ["dimred", "cloud", "spam"]  # ["cloud", "spam", "kddcup"]
  datasetsLocation = "/Users/yaseralkayale/Documents/classes/current/honours/kmeansII/finalDatasets/"
  algorithms = ["kmeans", "kmeans++", "kmeansNew"]  # ["kmeansNew"] #
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
  j = 0
  with open(filename) as f:
    for i, l in enumerate(f):
      j += 1
  return j
def analyze():
  ks = [10, 25, 50, 100]
  datasetNames = ["cloud", "spam", "kddcup"]
  algorithms = ["kmeans", "kmeans++", "kmeansNew"]
  root = "/Users/yaseralkayale/Documents/classes/current/honours/kmeansII/lib/scripts/new results/";


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
  for datasetName in datasetNames:
    for i in range(40):
      for algo in algorithms:
        file = open(root + datasetName + "/" + algo + "-out" + str(i) + ".extra")
        res = readFile(file);
        (inputFile, iterationTime, seedingTime, distance) = res
        k = numfile(root + datasetName + "/" + algo + "-out" + str(i))
        r = run(inputFile, iterationTime, seedingTime, distance, k, algo, datasetName)
        runs.append(r)

  distances = dict()
  runningTimes = dict()
  for algo in algorithms:
    distances[algo] = [r.distance for r in runs if r.algorithm == algo and r.k == 10]
    runningTimes[algo] = [r.seedingTime + r.iterationTime for r in runs if r.algorithm == algo]

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

def printFormattedTables():
  datasetNames = ["cloud", "spam", "dimred"]
  algorithms = ["kmeans", "kmeans++", "kmeansNew"]
  root = "/Users/yaseralkayale/Documents/classes/current/honours/kmeansII/lib/scripts/new results/";
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
  for datasetName in datasetNames:
    for i in range(80):
      for algo in algorithms:
        file = open(root + datasetName + "/" + algo + "-out" + str(i) + ".extra")
        res = readFile(file);
        (inputFile, iterationTime, seedingTime, distance), k = res, numfile(
          root + datasetName + "/" + algo + "-out" + str(i))
        r = run(inputFile, iterationTime, seedingTime, distance, k, algo, datasetName)
        runs.append(r)
  print("runs size:", len(runs))
  ks = [10, 25, 50, 100]
  for datasetName in datasetNames:
    # print(("{0:^145s}").format(datasetName))
    # print(("{0:4s} |{1:^47s}|{2:^47s}|{3:^47s}").format("", "Average Func", "Min Func", "Average Time"))
    # print(
    #   ("{0:>4s} |{1:^15s}|{2:^15s}|{3:^15s}|{4:^15s}|{5:^15s}|{6:^15s}|{7:^15s}|{8:^15s}|{9:^15s}").
    #     format("k", "Kmeans",
    #            "Kmeans++",
    #            "KmeansNew",
    #            "Kmeans",
    #            "Kmeans++",
    #            "KmeansNew",
    #            "Kmeans",
    #            "Kmeans++",
    #            "KmeansNew"))
    # print("-"*146)
    # for k in ks:
    #   distances = dict()
    #   runningTimes = dict()
    #   for algo in algorithms:
    #     distances[algo] = [r.distance for r in runs if r.algorithm == algo and r.k == k and r.datasetName == datasetName]
    #     runningTimes[algo] = [r.seedingTime + r.iterationTime for r in runs if r.algorithm == algo and r.k == k and r.datasetName == datasetName]
    #   print(("{0:4d} |{1:^15.2f}|{2:^15.2f}|{3:^15.2f}|{4:^15.2f}|{5:^15.2f}|{6:^15.2f}|{7:^15.2f}|{8:^15.2f}|{9:^15.2f}").
    #         format(k,
    #                sum(distances['kmeans']) / len(distances['kmeans']),
    #                sum(distances['kmeans++']) / len(distances['kmeans++']),
    #                sum(distances['kmeansNew']) / len(distances['kmeansNew']),
    #                min(distances['kmeans']),
    #                min(distances['kmeans++']),
    #                min(distances['kmeansNew']),
    #                sum(runningTimes['kmeans']) / len(runningTimes['kmeans']),
    #                sum(runningTimes['kmeans++']) / len(runningTimes['kmeans++']),
    #                sum(runningTimes['kmeansNew']) / len(runningTimes['kmeansNew'])
    #                ))

    print("\\begin{center}")
    print(
      "\\resizebox{\\textwidth}{!}{\\begin{tabular}{ |p{1cm}|p{1.3cm}|p{1.3cm}|p{1.3cm}|p{1.3cm}|p{1.3cm}|p{1.3cm}|p{1.3cm}|p{1.3cm}|p{1.3cm}| }")
    print("\\hline")
    print("& \\multicolumn{9}{c|}{" + datasetName + "}\\\\")
    print("\\cline{2-10}")
    print(
      "& \\multicolumn{3}{c|}{Average $\phi$} & \\multicolumn{3}{c|}{Minimum $\\phi$} & \\multicolumn{3}{c|}{Average $T$ (milliseconds)}\\\\");
    print("k")
    print("& \\multicolumn{1}{c}{kmeans} & \\multicolumn{1}{c}{kmeans++} & \\multicolumn{1}{c|}{kmeansNew}")
    print("& \\multicolumn{1}{c}{kmeans} & \\multicolumn{1}{c}{kmeans++} & \\multicolumn{1}{c|}{kmeansNew}")
    print("& \\multicolumn{1}{c}{kmeans} & \\multicolumn{1}{c}{kmeans++} & \\multicolumn{1}{c|}{kmeansNew}\\\\")
    print("    \hline")
    for k in ks:
      distances = dict()
      runningTimes = dict()
      for algo in algorithms:
        distances[algo] = [r.distance for r in runs if
                           r.algorithm == algo and r.k == k and r.datasetName == datasetName]
        runningTimes[algo] = [(r.seedingTime + r.iterationTime)*(10 ** (-6)) for r in runs if
                              r.algorithm == algo and r.k == k and r.datasetName == datasetName]
      f = ((
             "{0:4d} &{1:^15.2e}&{2:^15.2e}&{3:^15.2e}&{4:^15.2e}&{5:^15.2e}&{6:^15.2e}&{7:^15.2e}&{8:^15.2e}&{9:^15.2e}\\\\").
           format(k,
                  sum(distances['kmeans']) / len(distances['kmeans']),
                  sum(distances['kmeans++']) / len(distances['kmeans++']),
                  sum(distances['kmeansNew']) / len(distances['kmeansNew']),
                  min(distances['kmeans']),
                  min(distances['kmeans++']),
                  min(distances['kmeansNew']),
                  sum(runningTimes['kmeans']) / len(runningTimes['kmeans']),
                  sum(runningTimes['kmeans++']) / len(runningTimes['kmeans++']),
                  sum(runningTimes['kmeansNew']) / len(runningTimes['kmeansNew'])
                  ))
      f = re.sub('\+', '', f)
      print(f)
    print("\hline")
    print("\\end{tabular}}")
    print("\\end{center}")
    # print("="*146)

  # for algo in algorithms:
  #   distances[algo] = [r.distance for r in runs if r.algorithm == algo and r.k == 10]
  #   runningTimes[algo] = [r.seedingTime + r.iterationTime for r in runs if r.algorithm == algo]
  #
  # for algo in algorithms:
  #   print("Average over " + str(len(distances[algo])) + " runs for " + algo + ": " + str(
  #     sum(distances[algo]) / len(distances[algo])))
  # for algo in algorithms:
  #   print("Minimum over " + str(len(distances[algo])) + " runs for " + algo + ": " + str(
  #     min(distances[algo])))
# main()
# runFullExperiment();
printFormattedTables();
# analyze()
