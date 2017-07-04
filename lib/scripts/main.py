from plotExperimentCentres import *
import sys

with open(sys.argv[1]) as file:
  centres = readExperimentCentres(file)
  plotCentres(centres)
  plt.show()
  