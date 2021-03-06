from lib.scripts.experiment_instance import ExperimentInstance
from lib.scripts.experiment_cluster import Cluster

"""
Read the experiment runtimes given the file is in the correct format
"""

def readExperimentRuntimes(content):
  result = []
  for item in content:
    if item[:34] == 'Sum of distance squared to centre:':
      result.append(float(item[35:]))
  return result

"""
Given an iteratable, go over it and
extract all the 2d points.
"""

def readCentres(content):
  for item in content:
    if item[:6] == '<<<End':
      return
    temp = item.strip().split()
    if len(temp) != 2:
      print("Inpurity in Data ignored.")
      continue
    yield [float(temp[0]), float(temp[1])]

def readExperimentCentres(content):
  for item in content:
    if item[:3] == '***':
      yield readCentres(content)

def readTwoDFile(content):
  result = []
  for item in content:
    temp = item.strip().split()
    if len(temp) != 2:
      continue
    result.append([float(temp[0]), float(temp[1])])
  return result

def readCentres(file):
  centres = []
  for line in file:
    if line[:11] == "End Centres":
      break
    temp = line.strip().split()
    centres.append([float(temp[0]), float(temp[1])])
  return centres

def readExperiment(file):
  for inputLine in file:
    line = inputLine.strip().split(":")
    if len(line) == 0:
      continue
    elif line[0] == "Start Centres":
      centres = readCentres(file)
    elif line[0] == "End Experiment":
      result = ExperimentInstance(centres, algorithm, distanceToCentres, timeToPickSeeds, numIterations, timeToRunIterations)
      return result
    elif line[0] == "algorithm":
      algorithm = line[1]
    elif line[0] == "Sum of distance squared to centre":
      distanceToCentres = float(line[1])
    elif line[0] == "Time to pick the seeds":
      timeToPickSeeds = float(line[1])
    elif line[0] == "Number of iterations run":
      numIterations = int(line[1])
    elif line[0] == "Time to run the iterations":
      timeToRunIterations = float(line[1])
  return None

def readExperiments(fileName, dataset, maxExperiments=10, debug=False):
  ExperimentInstance.dataset = dataset
  Cluster.dataset = dataset
  with open(fileName) as file:
    result = []
    i = 0
    while maxExperiments > 0:
      temp = readExperiment(file)
      if temp == None:
        return result
      if debug:
        print("Experiment ", i, " has been read.")
      i = i + 1
      if len(result) > 0 and result[0].totalDistanceToCentres > temp.totalDistanceToCentres:
        result.insert(0, temp)
      else:
        result.append(temp)
      maxExperiments -= 1
  return result
