#!/usr/bin/python3

import numpy as np
import matplotlib.pyplot as plt
from pathlib import Path
import itertools
from generatedFiles.home import HOME

class Dataset:
  """
  To help us generate, print, and plot datasets given some parameters.
  """
  def __init__(self, sizes, means, covs=None):
    """

    :param sizes: The name of the datset file
    :param means: The name of the clusters file
    :param covs:
    """
    if type(sizes) == str:
      assert type(means) == str
      assert covs == None
      data= np.loadtxt(sizes,delimiter=',')
      self.centres = np.loadtxt(means,delimiter=',')
      clusterSize = int(len(data)/len(self.centres))
      self.clusters = [data[x:x+clusterSize] for x in range(0,len(data),clusterSize)]

    else:
      assert means != None
      assert covs != None

      self.sizes = sizes
      self.means = means
      self.covs = covs
      self.clusters = []
      for (size, mean, cov) in zip(sizes, means, covs):
        self.clusters.append(np.random.multivariate_normal(mean, cov, size))

  def plot(self, plt):
    s= [0.4 for n in range(len(self.clusters[0][:, 0]))]
    for cluster in self.clusters:
      plt.scatter(cluster[:, 0], cluster[:, 1],s=s)

  def printToFile(self):
    data = np.array(list(itertools.chain.from_iterable(self.clusters)))
    fileNum = 0;
    while Path((HOME + '/generatedFiles/dataset' + str(fileNum) + '.csv')).is_file():
      fileNum += 1;
    np.savetxt((HOME + '/generatedFiles/dataset' + str(fileNum) + ".csv"), data, delimiter=",")
    infoFileName = HOME + '/generatedFiles/dataset' + str(fileNum) + "-centres.csv"
    np.savetxt(infoFileName, self.means, delimiter=",")

"""
Every plot consists of 3 values
-The list of sizes of the clusters
-The list of means of each cluster
-The list of co-variances for each cluster
"""
plots = {
  1:([
       5000,
       5000,
       5000,
       5000
     ],
     [[-100000, -100000],
      [+100000, +100000],
      [-100000, +100000],
      [+100000, -100000]
      ],
     [[[700000000, 0], [0, 700000000]],
      [[700000000, 0], [0, 700000000]],
      [[700000000, 0], [0, 700000000]],
      [[700000000, 0], [0, 700000000]]
      ]
  ),
  2:([
       5000,
       5000,
       5000,
       5000
     ],
     [[-50000, -100000],
      [+50000, +100000],
      [-50000, +100000],
      [+50000, -100000]
      ],
     [[[700000000, 0], [0, 700000000]],
      [[700000000, 0], [0, 700000000]],
      [[700000000, 0], [0, 700000000]],
      [[700000000, 0], [0, 700000000]]
      ]
  ),
  3:([
       5000,
       5000,
       5000
     ],
     [
       [+60000, +60000],
       [-60000, +60000],
       [0, -60000]
     ],
     [[[900000000, 0], [0, 900000000]],
      [[900000000, 0], [0, 900000000]],
      [[900000000, 0], [0, 900000000]]
      ]
  ),
  4:([
       500,
       500,
       500,
       500,
       500
     ],
     [[0, 0],
      [-75000, -75000],
      [+75000, +75000],
      [-75000, +75000],
      [+75000, -75000]
      ],
     [[[90000000, 0], [0, 90000000]],
      [[90000000, 0], [0, 90000000]],
      [[90000000, 0], [0, 90000000]],
      [[90000000, 0], [0, 90000000]],
      [[90000000, 0], [0, 90000000]]
      ]
  ),
  5:([
       500,
       500,
       500,
       500,
       500
     ],
     [[0, 0],
      [-75000, -75000],
      [+75000, +75000],
      [-75000, +75000],
      [+75000, -75000]
      ],
     [[[900000000, 0], [0, 900000000]],
      [[900000000, 0], [0, 900000000]],
      [[900000000, 0], [0, 900000000]],
      [[900000000, 0], [0, 900000000]],
      [[900000000, 0], [0, 900000000]]
      ]
  )
}
def createDatasets(datasetInfo):
  """

  :param datasetInfo: A dictionary of datasets with values in format (sizes, means, covariance) of clusters
  :return:
  """
# datasets = []
# for key in plots:
#   (sizes, means, covs) = plots[key]
#   dataset = Dataset(sizes, means, covs)
#   dataset.printToFile()
#   plt.figure()
#   dataset.plot(plt)
# dataset = Dataset(HOME + '/generatedFiles/dataset4.csv',HOME + '/generatedFiles/dataset4-centers.csv')
# dataset.plot(plt)


plt.show()





