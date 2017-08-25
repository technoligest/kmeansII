import lib.scripts.experiment_plotters as plotter
import lib.scripts.experiment_analyzer as an
import lib.scripts.experiment_io as reader
import lib.scripts.experiment_utils as utils
import lib.scripts.experiment_serializer as sr



expr1id = 0
expr2id = 900
assert (abs(expr2id - expr1id) > 0)
datasetFile = "../../../inputFiles/DimRedFullDataComplete.txt"
with open(datasetFile) as file:
  dataset = reader.readTwoDFile(file)

experiments = sorted(sr.deserialize("../serializedExperiments/kmeans||-DimRedFullDataComplete.txt-test1.txt"),key=lambda exp:exp.distanceToCentres)
print("Done reading in first thing.")

# plotter.scatterPlotMatchings(experiments[expr1id], experiments[expr2id],
#                      lambda a, b:utils.distance(a.centre, b.centre))
# plotter.scatterPlotMatchings(experiments[expr1id], experiments[expr2id],
#                      lambda l1, l2:-1 * utils.overlap(l1.pointPositions, l2.pointPositions))
#
# k = [sum(i.averageDistancesOverArea) / len(i.averageDistancesOverArea) for i in experiments]
# k = [i.distanceToCentres for i in experiments]
analyzer = an.Analyzer(experiments, dataset)
print(analyzer.NIDs)

# print(analyzer.calcCliques([0,1]))

# k = analyzer.totalDistanceToCentres

# plotter.Plotter([k], xlabel="Total Distance To Centres", ylabel="Number of Experiments/total number of oxperiments",
#                 plotName="Objective Function Comparison").comparisonBarPlot()

plotter.plt.show()

"""
minimum weight perfect matching in terms of:
euclidean distance in terms of clusterCentres
max weight # common points
max weight intersection/union


find:
average (intersection/union)
(total # correctly classidied points/#points)-

Google: Ways to compare k-means results/clustering results (Email Vlado)

Meeting with vlado (Tuesday and Wednesday Afternoon)

"""
