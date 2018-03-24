import numpy as np
import matplotlib.pyplot as plt


def heatmap(twoD_Datast, resolution):
  x = twoD_Datast[:, 0]
  y = twoD_Datast[:, 1]
  heatmap, xedges, yedges = np.histogram2d(x, y, bins=resolution)
  extent = [xedges[0], xedges[-1], yedges[0], yedges[-1]]
  plt.clf()
  plt.imshow(heatmap.T, cmap="hot", extent=extent, origin='lower')
  plt.show()


sourcefile = "/Users/yaseralkayale/Documents/classes/current/honours/kmeansII/inputFiles/DimRedFullDataComplete.txt";
arr = np.loadtxt(sourcefile)
heatmap(arr, 250)
