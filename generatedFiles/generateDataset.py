#!/usr/bin/python3

import numpy as np
import matplotlib.pyplot as plt
from pathlib import Path
import itertools
from generatedFiles.home import HOME
from generatedFiles.Dataset import Dataset


"""
Every plot consists of 3 values
-The list of sizes of the clusters
-The list of means of each cluster
-The list of co-variances for each cluster
"""
plots = {
  "<10% overlap":
    ([
       5000,
       5000,
       5000,
       5000
     ],
     [[-1000, -1000],
      [+1000, +1000],
      [-1000, +1000],
      [+1000, -1000]
      ],
     [[[200000, 0], [0, 200000]],
      [[200000, 0], [0, 200000]],
      [[200000, 0], [0, 200000]],
      [[200000, 0], [0, 200000]]
      ]
  ),
  "50% overlap per pair of clusters":([
       5000,
       5000,
       5000,
       5000
     ],
     [[-500, -1000],
      [+500, +1000],
      [-500, +1000],
      [+500, -1000]
      ],
     [[[200000, 0], [0, 200000]],
      [[200000, 0], [0, 200000]],
      [[200000, 0], [0, 200000]],
      [[200000, 0], [0, 200000]]
      ]
  ),
  "~20% overlap":([
       5000,
       5000,
       5000
     ],
     [
       [+1000, +1000],
       [-1000, +1000],
       [0, -1000]
     ],
     [[[300000, 0], [0, 300000]],
      [[300000, 0], [0, 300000]],
      [[300000, 0], [0, 300000]],
      [[300000, 0], [0, 300000]]
      ]
  ),
  "~20% overlap ":([
       500,
       500,
       500,
       500,
       500
     ],
     [[0, 0],
      [-1000, -1000],
      [+1000, +1000],
      [-1000, +1000],
      [+1000, -1000]
      ],
     [[[300000, 0], [0, 300000]],
      [[300000, 0], [0, 300000]],
      [[300000, 0], [0, 300000]],
      [[300000, 0], [0, 300000]],
      [[300000, 0], [0, 300000]]
      ]
  ),
  5:([
       500,
       1000,
       1000,
       1000,
       1000
     ],
     [[0, 0],
      [-800, -800],
      [+800, +800],
      [-800, +800],
      [+800, -800]
      ],
     [[[10000, 0], [0, 10000]],
      [[250000, 0], [0, 250000]],
      [[250000, 0], [0, 250000]],
      [[250000, 0], [0, 250000]],
      [[250000, 0], [0, 250000]]
      ]
  )
}

def createDatasets(datasetInfo):
  """
  :param datasetInfo: A dictionary of datasets with values in format (sizes, means, covariance) of clusters
  :return:
  """
  datasets = []
  i=0
  dir = HOME + '/generatedFiles/datasets/'
  for key in plots:
    (sizes, means, covs) = plots[key]
    dataset = Dataset(sizes, means, covs)
    dataset.printToFile(dir)
    dataset.plot(plt)
    plt.show()
    i+=1
  plt.show()





