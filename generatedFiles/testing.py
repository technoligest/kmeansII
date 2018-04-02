# import numpy as np
import matplotlib.pyplot as plt
from generatedFiles.generateDataset import *
from generatedFiles.Dataset import Dataset

def showDatasets():
  for i in [0]:
    dir = HOME + '/generatedFiles/datasets/dataset'
    dataset = Dataset(dir + str(i) + '.csv', dir + str(i) + '-centres.csv')
    dataset.printToFile(HOME+'/generatedFiles/splitDatasets/',True,i)
    dataset.plot(plt)
  plt.show()

# createDatasets(plots)
showDatasets()
