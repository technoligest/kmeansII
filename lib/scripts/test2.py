import matplotlib.pyplot as plt
import numpy as np
import sys
# plt.plot(range(2), c="red")

# plt.figure()
# plt.plot(range(10), c="blue")

# plt.show()


def scatterPlot(data):
    plt.figure()
    for x,y in data:
        plt.plot(x,y,marker='o',
            fillstyle='full',
            markeredgecolor='red',
            markeredgewidth=0.0)

def readExperimentCentres(file):
    for item in file:
        v = [x.split(' ')[:2] for x in item.strip('\n').split(',')]
        yield [[float(a) for a in x]for x in v]

def plotMatchingCentres(fileName):
    with open(fileName) as file:
        iterator = readExperimentCentres(file)
        var =[]
        for k in iterator:
            var.append(k)
        scatterPlot(var)
        
# plotMatchingCentres(sys.argv[1])
# v=np.random.rand(50,2,2)
# scatterPlot(v)
# for i in v:
#     print(i)
#     print("hi")
# plt.show()