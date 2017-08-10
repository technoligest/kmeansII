import matplotlib.pyplot as plt

"""
Plots the given centres using a dotplot
"""
def plotCentres(centres):
  for x, y in centres:
    plt.plot(x, y, '.', label='line 1')

"""
Given a set of [x,y] coordinate
return 
"""
def convertToXY(l1):
  xVals = [x for x,y in l1]
  yVals = [y for x,y in l1]
  return (xVals, yVals)

def scatterPlot(data):
  plt.figure()
  for x,y in data:
    plt.scatter(x,y)

def connectedScatterPlot(data):
  plt.figure()
  for x, y in data:
    plt.plot(x, y, marker='o', fillstyle='full', markeredgewidth=0)

@property
def show():
  plt.show()