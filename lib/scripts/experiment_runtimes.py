import sys
from plotExperimentCentres import *


"""
Read the experiment runtimes given the file is in the correct format
"""
def readExperimentRuntimes(content):
  result =[]
  for item in content:
    if item[:34]=='Sum of distance squared to centre:':
      result.append (float(item[35:]))
  return result

"""
Function takes a stream and number of boxes,
it then splits the stream into that many boxes,
split evently according to the min and max of the items in that stream.
the values are returned as a list of pairs. Each pair has [numOfPoints, middleOfThisSection]
"""
def augment(arr, numSections):
  sorted(arr)
  minNum = arr[0]
  maxNum = arr[len(arr)-1]
  step = (maxNum-minNum)/numSections
  result = []
  currMax = minNum+step
  currNum = 0
  for i in arr:
    if i<=currMax:
      currNum+=1
    else:
      result.append([currNum,currMax-step/2])
      currMax+=step
      while i > currMax:
        result.append([0,currMax-step/2])
        currMax+=step
      currNum=1
  result.append([currNum,maxNum-step/2])
  return result
      

def plotExperimentRuntimes(fileName, yVal, numSections):
  with open(fileName) as file:
    experimentRuntimes = sorted(readExperimentRuntimes(file));
    sectionedData = augment(experimentRuntimes, numSections)
    plotX = [y for x,y in sectionedData]
    plotY = [yVal for x,y in sectionedData]
    plotAreas = [x*(experimentRuntimes[len(experimentRuntimes)-1]-experimentRuntimes[0])/len(experimentRuntimes)/numSections/2 for x,y in sectionedData]
    plt.scatter(plotX,plotY,s=plotAreas, alpha = 0.5)
    
    
