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
