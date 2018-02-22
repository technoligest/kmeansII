# import numpy as np
import matplotlib.pyplot as plt
from generatedFiles.generateDataset import *


for i in range(0,5):
  dataset = Dataset(HOME + '/generatedFiles/dataset'+str(i)+'.csv',HOME + '/generatedFiles/dataset'+str(i)+'-centres.csv')
  plt.figure()
  dataset.plot(plt)
plt.show()