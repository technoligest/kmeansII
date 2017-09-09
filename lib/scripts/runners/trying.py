import lib.scripts.experiment_perfect_matching as hung
# minim = min([min(k) for k in d])
# k = [[(i - minim) / 3184 for i in k] for k in d]
# print(k)

# d = [[1,1],[1,1]]
# print(hung.minimum_weight_perfect_matching(d))

#
#
# # import numpy as np
# # import matplotlib.pyplot as plt
# # import experiment_readers as rd
# # # Create data
# #
# # with open("../../inputFiles/DimRedFullDataComplete.txt") as file:
# #   centres = rd.readCentres(file)
# #
# # x = [x for x,y in centres]
# # y = [y for x,y in centres]
# #
# #
# # np.random.seed(0)
# # # example data
# # mu = 100  # mean of distribution
# # sigma = 15  # standard deviation of distribution
# # x = mu + sigma * np.random.randn(437)
# #
# # num_bins = 50
# #
# # fig, ax = plt.subplots()
# #
# # # the histogram of the data
# # n, bins, patches = ax.hist(x, num_bins, normed=1)
# #
# #
# # ax.set_xlabel('Smarts')
# # ax.set_ylabel('Probability density')
# # ax.set_title(r'Histogram of IQ: $\mu=100$, $\sigma=15$')
# #
# # # Tweak spacing to prevent clipping of ylabel
# # fig.tight_layout()
# # plt.show()
#
# import random
# # import numpy as np
# # import matplotlib.pyplot as plt
# #
# # fs = 10  # fontsize
# # pos = [1, 2, 4, 5, 7, 8]
# # data = [np.random.normal(0, std, size=100) for std in pos]
# #
# # fig, axes = plt.subplots(nrows=2, ncols=3, figsize=(6, 6))
# #
# # axes[0, 0].violinplot(data, pos, points=20, widths=0.3,
# #                       showmeans=True, showextrema=True, showmedians=True)
# # axes[0, 0].set_title('Custom violinplot 1', fontsize=fs)
# #
# # axes[0, 1].violinplot(data, pos, points=40, widths=0.5,
# #                       showmeans=True, showextrema=True, showmedians=True,
# #                       bw_method='silverman')
# # axes[0, 1].set_title('Custom violinplot 2', fontsize=fs)
# #
# # axes[0, 2].violinplot(data, pos, points=60, widths=0.7, showmeans=True,
# #                       showextrema=True, showmedians=True, bw_method=0.5)
# # axes[0, 2].set_title('Custom violinplot 3', fontsize=fs)
# #
# # axes[1, 0].violinplot(data, pos, points=80, vert=False, widths=0.7,
# #                       showmeans=True, showextrema=True, showmedians=True)
# # axes[1, 0].set_title('Custom violinplot 4', fontsize=fs)
# #
# # axes[1, 1].violinplot(data, pos, points=100, vert=False, widths=0.9,
# #                       showmeans=True, showextrema=True, showmedians=True,
# #                       bw_method='silverman')
# # axes[1, 1].set_title('Custom violinplot 5', fontsize=fs)
# #
# # axes[1, 2].violinplot(data, pos, points=200, vert=False, widths=1.1,
# #                       showmeans=True, showextrema=True, showmedians=True,
# #                       bw_method=0.5)
# # axes[1, 2].set_title('Custom violinplot 6', fontsize=fs)
# #
# # for ax in axes.flatten():
# #   ax.set_yticklabels([])
# #
# # fig.suptitle("Violin Plotting Examples")
# # fig.subplots_adjust(hspace=0.4)
# # plt.show()
#
#
#
#
#
# import experiment_plotters as pl
# import experiment_readers as rd
# import numpy as np
#
#
# def graphExperimentRuntimesFromFiles(list, names, numSections=10):
#   experimentRunTimes = []
#   for fileName in list:
#     with open(fileName) as file:
#       experimentRunTimes.append(rd.readExperimentRuntimes(file))
#       print(experimentRunTimes[len(experimentRunTimes)-1])
#   i = pl.Plotter(experimentRunTimes, names, numSections,xlabel="ExperimentRuntimes",ylabel="Algorithm")
#   i.comparisonBarPlot()
#
#
# experimentRunTimes = ["../experiments/Experiment Results/kmeans||-DimRedFullDataComplete.txt-test1.txt",
#                       "../experiments/Experiment Results/kmeans++-DimRedFullDataComplete.txt-test1.txt",
#                       "../experiments/Experiment Results/kmeans-DimRedFullDataComplete.txt-test1.txt"]
# names = ["kmeans||", "kmeans++", "kmeans"]
#
# graphExperimentRuntimesFromFiles(experimentRunTimes, names, 10)
# # s=[]
# # for i in range(1):
# #   s.append(np.random.normal(10,10,10000))
# # s=[-2.9825621174896169, -2.1504072978516175, -1.8727277730207839, -1.6603279347846613, -1.5685909271939782, -1.544327908578055, -1.4143527031291994, -1.4047393535737409, -1.2739416210646886, -1.2137230359526303, -1.1854084697079725, -1.0834269550781155, -1.0479990014653133, -1.032355941694201, -0.94929098784659038, -0.91748004352606871, -0.88063560936619856, -0.83236414835002392, -0.82731357999032018, -0.7651651805885632, -0.74122848716881296, -0.71328806652837251, -0.68899435779551821, -0.62423941083094348, -0.60654211246917422, -0.59770780917852162, -0.59372225108232213, -0.56467926957575587, -0.54502280394376046, -0.5378798574265683, -0.50380382033551496, -0.49987450308544534, -0.48412514994303252, -0.46632236327835808, -0.46587499832059776, -0.4514076229809954, -0.43832261873457351, -0.43535478751595436, -0.3860419669362305, -0.29199549240518796, -0.20617690035266534, -0.20510082686588513, -0.20447440173114126, -0.20148376921380989, -0.17986159097849017, -0.17529722390069249, -0.17453939187208603, -0.13460518073918207, -0.10361121112945761, -0.06500116129841943, -0.041886146236693268, -0.025515234833910262, -0.0066973255173395363, 0.0031471030121456235, 0.01192617855519908, 0.06048545956704432, 0.086076720381265334, 0.098387936107619603, 0.12201128242638121, 0.15861231126985356, 0.16413683316115552, 0.18150604322871045, 0.18962594562018997, 0.20171773343814911, 0.2495714623108749, 0.27000723500313945, 0.27292423268454497, 0.27998632202726953, 0.33344673844647715, 0.36081701836252306, 0.39898176699788374, 0.40443585069807841, 0.412777635731717, 0.44004330188776825, 0.46935125843822378, 0.5126810028932185, 0.62837418910270459, 0.6440771819719926, 0.67850656615720151, 0.70956855209993452, 0.73640605716094953, 0.77738465732856143, 0.80057388501254856, 0.80451468583447328, 0.83344211533329604, 0.85615481146064254, 0.92252433971434511, 1.2099382387989082, 1.2373579827168568, 1.290889432400022, 1.3153722173610876, 1.356596516612631, 1.3803531034848353, 1.4518047322229708, 1.4656917810048662, 1.6103076487297532, 1.6840811302700063, 1.7966074532835101, 2.0522379723465045, 2.2004210436288565]
#
# # i= pl.Plotter(s)
# # i.comparisonBubblePlot()
# pl.Plotter.show()
#
# # # a stacked bar plot with errorbars
# # import numpy as np
# # import matplotlib.pyplot as plt
#
#
# # N = 5
# # menMeans = (20, 35, 30, 35, 27)
# # womenMeans = (25, 32, 34, 20, 25)
# # womennMeans = (25, 32, 34, 20, 25)
# # width = 10       # the width of the bars: can also be len(x) sequence
# # ind = [i*20 for i in np.arange(N)]    # the x locations for the groups
# #
# # # p1 = plt.bar(ind, menMeans, width, color='#d62728',)
# # # p2 = plt.bar(ind, womenMeans, width, bottom=menMeans)
# #
# # p1 = plt.bar(ind, menMeans, width, color='#d62728')
# # p2 = plt.bar(ind, womenMeans, width, menMeans)
# #
# # plt.ylabel('Scores')
# # plt.title('Scores by group and gender')
# # plt.xticks(ind, ('G1', 'G2', 'G3', 'G4', 'G5'))
# # plt.yticks(np.arange(-10, 81, 5))
# #
# # plt.legend((p1[0], p2[0]), ('Men', 'Women'))
# #
# # plt.show()
# # rn.plt.show()
#
#
#
# """
#

# import lib.scripts.experiment_serializer as ser
# import lib.scripts.experiment_plotters as plt
# import numpy as np
# import lib.scripts.experiment_convex_hull as hull
# import random as rand
# import lib.scripts.experiment_io as reader
# print(rand.random())
# def decreaseDatasetSize():
#   datasetFile = "../../../inputFiles/DimRedFullDataComplete.txt"
#   with open(datasetFile) as file:
#     dataset = reader.readTwoDFile(file)
#   result=[]
#   for i in range(10000):
#     result.append(dataset[rand.random()*len(dataset)])
#   return result
#
#
# import lib.scripts.experiment_utils as utils
# import numpy as np
#
# datasetFile = "../../../inputFiles/DimRedFullDataComplete.txt"
# with open(datasetFile) as file:
#   dataset = reader.readTwoDFile(file)
#
# i = utils.splitIntoXY(dataset[:20000])
# x = np.array(i[0])
# y = np.array(i[1])
# plt.plotHeetMap(x,y)
# plt.show()



# def listToString(l):
#   result = ""
#   for i in l:
#     result += str(i)
#   return result
# il = dict()
# k = [1, 2, 3, 4, 5, 5]
# z = [1, 2, 3, 4, 5, 5]
# il[str(k)] = 17
# il[str(z)] = 20
# print(il)


import lib.scripts.experiment_serializer as sr
import lib.scripts.experiment_io as reader
import lib.scripts.experiment_cluster as cl
import time
import lib.scripts.experiment_utils as utils
import lib.scripts.strongly_connected_componenents as scc
experiments = sr.deserialize("../serializedExperiments/NewExperimentskmeans||.txt")
datasetFile = "../../../inputFiles/DimRedFullDataComplete.txt"
with open(datasetFile) as file:
  cl.Cluster.dataset = reader.readTwoDFile(file)

mat = utils.adjacencyMatrix(experiments[0].clusters,experiments[1].clusters,lambda a, b:bin(a.binaryPointPositions & b.binaryPointPositions).count("1") - 1)
mat2 = utils.fastAdjacencyMatrix(experiments[0].clusters,experiments[1].clusters)

assert(len(mat)==len(mat2))

for i in range(len(mat)):
  print(mat[i])
  print(mat2[i])
  print()


