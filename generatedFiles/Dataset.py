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
      """
      Here the dataset is passed
      """
      assert type(means) == str
      assert covs == None
      data = np.loadtxt(sizes, delimiter=',')
      centresArray = np.loadtxt(means, delimiter=',')
      self.centres = centresArray[:,0:2]
      print( self.centres);
      clusterSizes = centresArray[:,2:3].T[0]
      print("sizes: "+str(clusterSizes))
      print("sum: "+ str(sum(clusterSizes))+", len: " + str(len(data)))
      assert(sum(clusterSizes) == len(data))

      clusterPos = np.insert(np.cumsum(clusterSizes),0,0)
      print(clusterPos)
      self.clusters = [data[int(clusterPos[x-1]):int(clusterPos[x])] for x in range(1, len(clusterPos))]
    else:
      """
      Here we need to generate the dataset
      """
      assert means != None
      assert covs != None

      self.sizes = sizes
      self.centres = means
      self.covs = covs
      self.clusters = []
      for (size, mean, cov) in zip(sizes, means, covs):
        self.clusters.append(np.random.multivariate_normal(mean, cov, size))

  def plot(self, plt):
    plt.figure();
    s = [0.4 for n in range(len(self.clusters[0][:, 0]))]
    for cluster in self.clusters:
      print("Plotting")
      plt.scatter(cluster[:, 0], cluster[:, 1], s=s)
    print()

  def printToFile(self,dir,splitClusters=False, fileNum =None):
    if splitClusters:
      assert(fileNum!=None)
      for cluster,i in zip(self.clusters,range(len(self.clusters))):
        np.savetxt(dir+'dataset' + str(fileNum) + "-cluster-"+str(i)+".csv", cluster, delimiter=",")
    else:
      fileNum = 0;
      while Path(dir+'dataset' + str(fileNum) + '.csv').is_file():
        fileNum += 1;
      data = np.array(list(itertools.chain.from_iterable(self.clusters)))
      np.savetxt(dir+'dataset' + str(fileNum) + '.csv', data, delimiter=",")
      centresFileName = HOME + '/generatedFiles/datasets/dataset' + str(fileNum) + "-centres.csv"
      arr = np.array([np.append(centre,len(cluster)) for centre,cluster in zip(self.centres,self.clusters)])
      np.savetxt(centresFileName, arr, delimiter=",")
