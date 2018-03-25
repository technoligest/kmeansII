import numpy as np
import matplotlib.pyplot as plt


def heatmap(twoD_Datast, resolution):
  x = twoD_Datast[:, 0]
  y = twoD_Datast[:, 1]
  heatmap, xedges, yedges = np.histogram2d(x, y, bins=resolution)
  print(str(len(heatmap))+"---"+str(len(heatmap[0])))
  extent = [xedges[0], xedges[-1], yedges[0], yedges[-1]]
  plt.clf()
  im = plt.imshow(heatmap.T, cmap="hot", extent=extent, origin='lower')
  plt.tick_params(
    # axis='both',          # changes apply to the x-axis
    which='both',      # both major and minor ticks are affected
    bottom='off',      # ticks along the bottom edge are off
    top='off',         # ticks along the top edge are off
    labelbottom='off')
  # i = plt.colorbar(im)
  i = plt.colorbar(im,ticks=[0,  71])
  i.ax.set_yticklabels(['Low', 'High'])
  plt.show()



sourcefile = "/Users/yaseralkayale/Documents/classes/current/honours/kmeansII/inputFiles/DimRedFullDataComplete.txt";
arr = np.loadtxt(sourcefile)
heatmap(arr, 250)
