from main import *

"""
Reads the number of given centres from a file.
The centres must be 2-d
"""
def readMyCentres(numCentres,file):
    result =[]
    for i in range(numCentres):
        temp=file.readline().strip().split()
        while len(temp)<2:
            temp=file.readline().strip().split()
        result.append( [float(temp[0]),float(temp[1])])
    print(result)
    return result
    
numCentres=50
with open(sys.argv[1]) as file:
    t.scatterPlot(splitIntoXY(readMyCentres(numCentres,file),readMyCentres(numCentres,file)))
    t.plt.show()
    

    
