from scipy.stats import gaussian_kde
import matplotlib.pyplot as plt
import numpy as np

import lib.scripts.experiment_perfect_matching as hung
import lib.scripts.experiment_utils as utils

def plotHeetMap(x, y):
  # Calculate the point density
  xy = np.vstack([x, y])
  z = gaussian_kde(xy)(xy)

  # Sort the points by density, so that the densest points are plotted last
  idx = z.argsort()
  x, y, z = x[idx], y[idx], z[idx]

  fig, ax = plt.subplots()
  ax.scatter(x, y, c=z, s=50, edgecolor='')


"""
Plots the given centres using a dotplot
"""
def plotCentres(centres):
  plt.figure()
  for x, y in centres:
    plt.plot(x, y, '.', label='line 1', c="r")


"""
Given a set of [x,y] coordinate
return 
"""
def convertToXY(l1):
  xVals = [x for x, y in l1]
  yVals = [y for x, y in l1]
  return (xVals, yVals)

def scatterPlot(data):
  plt.figure()

  for x, y in data:
    plt.scatter(x, y)

def connectedScatterPlot(data):
  plt.figure()
  for x, y in data:
    plt.plot(x, y, marker='o', fillstyle='full', markeredgewidth=0)

def show():
  plt.show()


"""
Given two experiments and a function to evaluate their 
adjacency matrix.
plot the matchings between these two experiment centres
"""
def scatterPlotMatchings(e1, e2, func):
  d = utils.adjacencyMatrix(e1.clusters, e2.clusters, func)
  minimum = min([min(x) for x in d])
  if minimum < 0:
    d = [[item - minimum for item in row] for row in d]
  matchings = hung.minimum_weight_perfect_matching(d)
  pairs1 = e1.centres
  pairs2 = [e2.centres[p] for p, _ in matchings]
  connectedScatterPlot(utils.splitIntoXY(pairs1, pairs2))


"""
plot 1-d values
"""
class Plotter:
  """
  Help plotting functions to set the names of the plots
  """
  def plot(plotFunction):
    def wrapper(self,*args):
      plotFunction(self,*args)
      plt.ylabel(self.ylabel)
      plt.xlabel(self.xlabel)
      plt.title(self.plotName)
    return wrapper
  @staticmethod
  def show():
    plt.show()

  def __init__(self, values, valueNames=None, numSections=10, ylabel="", xlabel="", plotName=""):
    if valueNames != None:
      assert (len(valueNames) == len(values))
    self.plotName = plotName
    self.valueNames = valueNames
    self.values = [sorted(i) for i in values]
    self.percentageColours = ['#ffffcc', '#E8FF0C', '#FF6600', '#E82C0C', '#FF6600', '#E8FF0C', '#ffffcc']
    self.numSections = numSections
    self.xlabel = xlabel
    self.ylabel = ylabel

  def setxyticksBarPlot(self, maxY=1):
    minimum = min(x[0] for x in self.values if len(x) > 0)
    maximum = max(x[len(x) - 1] for x in self.values if len(x) > 0)
    if int((maximum - minimum) / 10) == 0:
      step = 1
    else:
      step = 10 ** (len(str(int((maximum - minimum) / 10))))
    minimum = minimum - (minimum % step)
    plt.xticks(np.arange(minimum, maximum + step, step))
    y = np.arange(0, maxY, 0.05)
    self.axes.set_yticks(y)
    self.valueNames = [str(i * 100) + "%" for i in y]
    self.axes.set_yticklabels(self.valueNames)

  def setxyticksBubblePlot(self, yValueSeparator):
    minimum = min(x[0] for x in self.values if len(x) > 0)
    maximum = max(x[len(x) - 1] for x in self.values if len(x) > 0)
    if int((maximum - minimum) / 10) == 0:
      step = 1
    else:
      step = 10 ** (len(str(int((maximum - minimum) / 10))))
    minimum = minimum - (minimum % step)
    plt.xticks(np.arange(minimum, maximum + step, step))
    y = np.arange(yValueSeparator, (1 + len(self.values)) * yValueSeparator, yValueSeparator)
    self.axes.set_yticks(y)
    if self.valueNames != None:
      self.axes.set_yticklabels(self.valueNames)
    else:
      self.axes.set_yticklabels(range(1, len(self.values) + 1))

  def barPlot(self, experimentRuntimes):
    sectionedData = self.augment(experimentRuntimes)
    plotX = [y for x, y in sectionedData]
    plotY = [x for x, y in sectionedData]
    barSize = 0.05 * max(plotY)
    self.axes.bar(plotX, plotY, plotX[1] - plotX[2])
    # Adding the heatmap thing 50%, 75%, 90%
    t = self.findTuple(experimentRuntimes)
    bottom = experimentRuntimes[0]
    for i, colour in zip(t, self.percentageColours):
      self.axes.barh(-2 * barSize, [i], barSize, [bottom], color=colour)
      bottom = bottom + i
    self.setxyticksBarPlot(max(plotY) * 1.3)
  @plot
  def comparisonBarPlot(self):
    for experiment in self.values:
      self.fig, self.axes = plt.subplots()
      self.barPlot(experiment)
  @plot
  def comparisonBubblePlot(self):
    self.fig, self.axes = plt.subplots()
    valueSeparator = 5
    currYval = valueSeparator
    for experiment in self.values:
      self.bubblePlotExperimentRuntimes(experiment, currYval)
      currYval = currYval + valueSeparator
    self.setxyticksBubblePlot(valueSeparator)
  # Probability that I exceesd a given value
  # y-value, the number of values of this point or higher
  # x-value, is the runtime value
  @plot
  def plotCascadingPlot(self):
    for val in self.values:
      self.fig, self.axes = plt.subplots()
      self.cascadingPlot(val)


  def cascadingPlot(self, l):
    l = sorted(l)
    cumulList = [[l[i], len(l) - i] for i in range(len(l))]
    x, y = convertToXY(cumulList)
    plt.plot(x, y, marker='o', fillstyle='full', markeredgewidth=0)


  """
  Given a list of numbers, give the list of percentiles
  This helpts us create a density concentration graph
  """
  def findTuple(self, items):
    size = len(items)
    minimum = items[0]
    temp = [5, 12.5, 25, 75, 87.5, 95, 99.999999999]
    assert (len(temp) == len(self.percentageColours))
    cumul = minimum
    result = []
    for i in temp:
      result.append(items[int(size / 100 * i)] - cumul)
      cumul = cumul + result[len(result) - 1]
    return result

  def bubblePlotExperimentRuntimes(self, experimentRuntimes, yVal):
    # This gives us the value for the sizes of each bar (for use later)
    sectionedData = self.augment(experimentRuntimes)
    plotX = [y for x, y in sectionedData]
    plotY = [yVal for _ in sectionedData]
    plotAreas = [x * (experimentRuntimes[len(experimentRuntimes) - 1] - experimentRuntimes[0]) / self.numSections / 2
                 for x, y in sectionedData]
    self.axes.scatter(plotX, plotY, s=plotAreas, alpha=0.5)

    # plotting the mean, max and min
    vplot = self.axes.violinplot([experimentRuntimes], [yVal - 1], vert=False, showmeans=True, showmedians=True)
    vplot['cmeans'].set_color('red')
    vplot['cmedians'].set_color('blue')

    # Adding the heatmap thing 50%, 75%, 90%
    t = self.findTuple(experimentRuntimes)
    bottom = experimentRuntimes[0]
    for i, colour in zip(t, self.percentageColours):
      self.axes.barh(yVal - 2, [i], 0.35, [bottom], color=colour)
      bottom = bottom + i


  """
  Function takes a stream and number of boxes,
  it then splits the stream into that many boxes,
  split evently according to the min and max of the items in that stream.
  the values are returned as a list of pairs. Each pair has [numOfPoints, middleOfThisSection]
  """
  def augment(self, arr):
    minNum = arr[0]
    maxNum = arr[len(arr) - 1]
    step = (maxNum - minNum) / self.numSections
    result = []
    currMax = minNum + step
    currNum = 0
    for i in arr:
      if i <= currMax:
        currNum += 1
      else:
        result.append([currNum, currMax - step / 2])
        currMax += step
        while i > currMax:
          result.append([0, currMax - step / 2])
          currMax += step
        currNum = 1
    result.append([currNum, maxNum - step / 2])
    summ = sum([x for x, y in result])
    return [[x / summ, y] for x, y in result]
