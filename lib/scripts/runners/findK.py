import os
import subprocess
import numpy as np
import lib.scripts.experiment_utils as utils
from lib.scripts.experiment_perfect_matching import minimum_weight_perfect_matching, maximum_weight_perfect_matching
import matplotlib.pyplot as plt
import sys
from threading import Thread

def calcPointPositions(dataset, centres):
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

def runExperiments(inputFileName, k, executable):
  outFiles = []
  tempFile = "aaaaaaaatemp"
  for i in range(k):
    runExperiment(executable, k,
                  inputFileName=inputFileName,
                  outputFileName=tempFile + str(i),
                  algorithm="kmeans++")
  centres = []
  for i in range(k):
    centres.append(np.loadtxt(tempFile + str(i), float, delimiter=","))
  # Deleting all the temporary files.
  for i in range(k):
    os.remove(tempFile + str(i))
    os.remove(tempFile + str(i) + ".extra")
  return centres

@utils.printRunningTime
def calcMatchings(dataset, centres):
  matchings = dict()
  for centres1Id in range(len(centres) - 1):
    for centres2Id in range(centres1Id + 1, len(centres)):
      centres1 = centres[centres1Id]
      centres2 = centres[centres2Id]
      pos1 = calcPointPositions(dataset, centres1)
      pos2 = calcPointPositions(dataset, centres2)
      distances = utils.adjacencyMatrix(pos1, pos2, lambda p1, p2:utils.overlap(p1, p2));
      matching = maximum_weight_perfect_matching(distances)
      matchings[(centres1Id, centres2Id)] = [a for a, _ in matching]
      # plt.figure();
      # for m in matching:
      #   x, y = utils.splitIntoXY([centres2[m[0]], centres1[m[1]]])
      #   plt.plot(x, y, marker='o', fillstyle='full', markeredgewidth=0)
  return matchings

class Node:
  def __init__(self, name):
    self.name = name
    self.neighbours = []
    self.visited = False
def buildGraph(matchings, numRuns):
  if len(matchings) == 0:
    return None
  size = len(next(iter(matchings.values())))
  for i in matchings:
    assert (len(matchings[i]) == size)
  nodes = dict()
  for runId in range(numRuns):
    for clusterId in range(size):
      nodeId = (runId, clusterId)
      nodes[nodeId] = Node(nodeId)

  for matchingId in matchings:
    centres1id, centres2id = matchingId
    matching = matchings[matchingId]
    for runId in range(numRuns):
      node1 = nodes[(centres1id, runId)]
      node2 = nodes[(centres2id, matching[runId])]
      node1.neighbours.append(node2)
      node2.neighbours.append(node1)
  return nodes
def graphSize(node):
  if node.visited:
    return 0
  node.visited = True
  size = 1
  for neighbour in node.neighbours:
    size += graphSize(neighbour)
  return size

def cliqueSizes(inputFileName, k, executable):
  dataset = np.loadtxt(inputFileName, float, delimiter=",")
  centres = runExperiments(inputFileName, k, executable)  # set of all centres over all runs
  matchings = calcMatchings(dataset, centres)
  graph = buildGraph(matchings, k)
  cliqueSizes = [graphSize(graph[subgraphName]) for subgraphName in graph if not graph[subgraphName].visited]
  print(cliqueSizes)
  return cliqueSizes

def group(values):
  values = np.array(sorted(values))
  dif = np.ones(values.shape, values.dtype)
  dif[1:] = np.diff(values)
  idx = np.concatenate((np.where(dif)[0], [len(values)]))
  vals = values[idx[:-1]]
  count = np.diff(idx)
  return (vals, count)
def findK(executableName, maxk, inputFileName):
  res = sorted([len(cliqueSizes(inputFileName, maxk, executableName)) for _ in range(10)])
  g = group(res)
  return [a for a, b in sorted(zip(g[0], g[1]), key=lambda z:z[1])][-1]

executableName = "/Users/yaseralkayale/Documents/classes/current/honours/kmeansII/cmake-build-debug/kmeans"
k = 6
inputFileName = "/Users/yaseralkayale/Documents/classes/current/honours/kmeansII/generatedFiles/datasets/dataset0.csv"
print("The answer is: ", findK(executableName, k, inputFileName))
