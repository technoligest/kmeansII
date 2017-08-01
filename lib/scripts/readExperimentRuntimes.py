import sys
from plotExperimentCentres import *

numBoxes = 10

def readExperimentRuntimes(content):
  result =[]
  for item in content:
    if item[:34]=='Sum of distance squared to centre:':
      result.append (float(item[35:]))
  return result


def augment(arr):
  minNum = arr[0]
  maxNum = arr[len(arr)-1]
  step = (maxNum-minNum)/numBoxes
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
      

def readFile(i,fileName):
  with open(fileName) as file:
    iterator = readExperimentRuntimes(file)
    var = sorted(iterator)
    var3 = augment(var)
    plotX = [y for x,y in var3]
    plotY = [i for x,y in var3]
    plotAreas = [x*(var[len(var)-1]-var[0])/len(var)/numBoxes/2 for x,y in var3]
    plt.scatter(plotX,plotY,s=plotAreas, alpha = 0.5)
    

    # var2 =[[x,i]for x in var]
    # plotCentres(var2)
    

plt.figure()
readFile(-1, '../experiments/Experiment Results/kmeans-DimRedFullDataComplete.txt-test0.txt')
readFile(0, '../experiments/Experiment Results/kmeans++-DimRedFullDataComplete.txt-test0.txt')
readFile(1,'../experiments/Experiment Results/kmeans||-DimRedFullDataComplete.txt-test0.txt')
plt.show()
