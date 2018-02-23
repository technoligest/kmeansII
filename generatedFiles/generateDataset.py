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
  1:([
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
  2:([
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
  3:([
       5000,
       5000,
       5000
     ],
     [
       [+1000, +1000],
       [-1000, +1000],
       [0, -1000]
     ],
     [[[250000, 0], [0, 250000]],
      [[250000, 0], [0, 250000]],
      [[250000, 0], [0, 250000]],
      [[250000, 0], [0, 250000]]
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
  datasets = []
  i=0
  for key in plots:
    print("----"+str(key))
    (sizes, means, covs) = plots[key]
    dataset = Dataset(sizes, means, covs)
    dataset.printToFile()
    dataset.plot(plt)
    plt.show()
    i+=1
    if i==3:
      break



  plt.show()





