import matplotlib.pyplot as plt

def readCentres(content):
  toPlotX = []
  toPlotY = []
  for item in content:
    if item[:6]=='<<<End':
      return [toPlotX,toPlotY]
    temp = item.strip().split()
    if len(temp) !=2:
      continue
    print(temp)
    toPlotX.append(temp[0])
    toPlotY.append(temp[1])
  return []

def readExperimentCentres(content):
  result = []
  for item in content:
    print(item[:3])
    if item[:3] == '***':
      centres = readCentres(content)
      result.append([centres[0], centres[1]])
  return result

def dotPlot(x,y):
  plt.plot(x, y, '.', label='line 1')

def plotCentres(centres):
  for x,y in centres:
    dotPlot(x,y)  

# print (sys.argv[0])
def readTwoDFile(content):
  toPlotX = []
  toPlotY = []
  for item in content:
    temp = item.strip().split()
    if len(temp) !=2:
      continue
    print(temp)
    toPlotX.append(temp[0])
    toPlotY.append(temp[1])


# print(content)
# cnt= [[float(y) for y in x.strip().split()][0] for x in content]


