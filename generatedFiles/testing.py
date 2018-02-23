# import numpy as np
import matplotlib.pyplot as plt
from generatedFiles.generateDataset import *
from generatedFiles.Dataset import Dataset

createDatasets(plots)
# for i in range(7,8):
#   dataset = Dataset(HOME + '/generatedFiles/dataset'+str(i)+'.csv',HOME + '/generatedFiles/dataset'+str(i)+'-centres.csv')
#   plt.figure()
#   dataset.plot(plt)
# plt.show()