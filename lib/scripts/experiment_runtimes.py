import matplotlib.pyplot as plt


class ComparisonPlotter:
  def show(self):
    plt.show()

  def __init__(self, values, numSections=10, ylabel="", xlabel=""):
    self.values = values
    self.percentageColours = ['#E8FF0C', '#FF6600', '#E82C0C', '#FF6600', '#E8FF0C']
    self.numSections = numSections
    self.fig, self.axes = plt.subplots()
    plt.ylabel(ylabel)
    plt.xlabel(xlabel)

  def plot(self):
    experimentSeparator = 5
    currYval = experimentSeparator
    for experiment in self.values:
      experiment = sorted(experiment)
      self.bottom = experiment[0]
      self.plotExperimentRuntimes(experiment, currYval)
      currYval = currYval + experimentSeparator

  def findTuple(self, items):
    items = sorted(items)
    size = len(items)
    minimum = int(items[0])
    left75 = items[int(size / 100 * 12.5)] - minimum
    left50 = items[int(size / 100 * 25)] - minimum - left75
    right50 = items[int(size / 100 * 62.5)] - minimum - left50 - left75
    right75 = items[int(size / 100 * 87.5)] - minimum - left50 - left75 - right50
    maximum = int(items[size - 1]) - minimum - left50 - left75 - right50 - right75
    result = [left75, left50, right50, right75, maximum]
    return result

  def plotExperimentRuntimes(self, experimentRuntimes, yVal):
    # This gives us the value for the sizes of each bar (for use later)
    sectionedData = self.augment(experimentRuntimes)
    plotX = [y for x, y in sectionedData]
    plotY = [yVal for _ in sectionedData]
    plotAreas = [x * (experimentRuntimes[len(experimentRuntimes) - 1] - experimentRuntimes[0]) / len(
      experimentRuntimes) / self.numSections / 2 for x, y in sectionedData]
    self.axes.scatter(plotX, plotY, s=plotAreas, alpha=0.5)

    # plotting the mean, max and min
    vplot = self.axes.violinplot([experimentRuntimes], [yVal - 1], vert=False, showmeans=True, showmedians=True)
    vplot['cmeans'].set_color('red')
    vplot['cmedians'].set_color('blue')

    # Adding the heatmap thing 50%, 75%
    t = self.findTuple(experimentRuntimes)

    colourIndex = 0

    for i in t:
      self.axes.barh(yVal - 2, [i], 0.35, [self.bottom], color=self.percentageColours[colourIndex])
      colourIndex = colourIndex + 1
      self.bottom = self.bottom + i

  """
  Function takes a stream and number of boxes,
  it then splits the stream into that many boxes,
  split evently according to the min and max of the items in that stream.
  the values are returned as a list of pairs. Each pair has [numOfPoints, middleOfThisSection]
  """

  def augment(self, arr):
    sorted(arr)
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
    return result
