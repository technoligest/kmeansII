import matplotlib.pyplot as plt

"""
Given an iteratable, go over it and
extract all the 2d points.
"""
def readCentres(content):
  for item in content:
    if item[:6]=='<<<End':
      return 
    temp = item.strip().split()
    if len(temp) !=2:
      print("Inpurity in Data ignored.")
      continue
    yield [float(temp[0]),float(temp[1])]
  


def readExperimentCentres(content):
  for item in content:
    if item[:3] == '***':
      yield readCentres(content)
  


# print (sys.argv[0])
def readTwoDFile(content):
  for item in content:
    temp = item.strip().split()
    if len(temp) !=2:
      continue
    print(temp)
    yield([float(temp[0]),float(temp[1])])
