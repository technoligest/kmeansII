import pickle

import os

import lib.scripts.experiment_io as reader
import lib.scripts.experiment_instance as inst


def serialize(filename, object):
  with open(filename, 'wb') as f:
    pickle.dump(object, f)


def deserialize(filename):
  with open(filename, 'rb') as f:
    return pickle.load(f)

expr1id = 0
expr2id = 1
assert (abs(expr2id - expr1id) > 0)


def serializeEntireExperimentsDirectory(directory, datasetFileName):
  with open(datasetFileName) as file:
    dataset = reader.readTwoDFile(file)
  for file in os.listdir(os.fsencode(directory)):
    filename = os.fsdecode(file)
    if filename.endswith(".txt") or filename.endswith(".py"):
      experimentsFile = directory + filename
      experiments = reader.readExperiments(experimentsFile, dataset,200000)
      serialize("serializedExperiments/" + filename,experiments)

# directory = "../experiments/Experiment Results/"
# datasetFile = "../../inputFiles/DimRedFullDataComplete.txt"
# serializeEntireExperimentsDirectory(directory,datasetFile)

# experimentsFile = "../experiments/Experiment Results/kmeans-DimRedFullDataComplete.txt-test1.txt"
# datasetFile = "../../inputFiles/DimRedFullDataComplete.txt"
# experiments, dataset = reader.readExperiments(experimentsFile, datasetFile, max(expr1id, expr2id) + 1)
#
# # serialize("dataset.txt", dataset)
# # serialize("experiments.txt",experiments)
#
# i = deserialize("experiments.txt")
# for k in i:
#   print(k)
# print(len(i))
