import matplotlib.pyplot as plt
import numpy as np
import sys

def scatterPlot(data):
    plt.figure()
    for x,y in data:
        plt.plot(x,y,marker='o',fillstyle='full', markeredgewidth=1.0)

def readExperimentCentres(file):
    for item in file:
        v = [x.split(' ')[:2] for x in item.strip('\n').split(',')]
        yield [[float(a) for a in x]for x in v]

def plotMatchingCentres(fileName):
    with open(fileName) as file:
        scatterPlot(readExperimentCentres(file))
        
# plotMatchingCentres(sys.argv[1])
# v=np.random.rand(50,2,2)
# scatterPlot(v)
# for i in v:
#     print(i)
#     print("hi")
# plt.show()