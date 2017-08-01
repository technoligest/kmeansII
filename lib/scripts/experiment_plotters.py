import matplotlib.pyplot as plt

"""
Plots the given centres
"""
  

def plotCentres(centres):
  for x,y in centres:
    plt.plot(x, y, '.', label='line 1')
    
def convertToXY(l1):
  x=[l[0] for l in l1]
  y=[l[1] for l in l1]
  return (x,y)
  
  
def scatterPlot(data):
    plt.figure()
    print(len(data))
    for x,y in data:
        plt.plot(x,y,marker='o',fillstyle='full', markeredgewidth=1.0)
