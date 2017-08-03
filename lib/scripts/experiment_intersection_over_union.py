from distance import findBelongingCentrePosition, findDistanceMatrix
from hungarian import minimum_weight_perfect_matching
class calcIntersections:
  def rearrangeClusterCentres(self, baseExperiment, otherExperiments):
    matchings = minimum_weight_perfect_matching(findDistanceMatrix(baseExperiment.centres, otherExperiments.centres))
    baseExperiment.centres=[baseExperiment[x] for x,_ in matchings]
  def calcNorbertArray(self):
    for i in range(1,len(self.experiments)):
      rearrangeClusterCentres(experiments[0], experiments[i])
    return [[findBelongingCentrePosition(self.dataset[instId],self.experiments[experimentId].centres) for intId in range(len(self.dataset))]for experimentId in range(len(self.experiments))]
  
  def __init__(self, dataset, experiments):
    self.dataset=dataset
    self.experiments=experiments
    self.norbertArray= self.calcNorbertArray()
    
  


def calcIntersectionOverUnion(dataset, experiments):
  return calcIntersections(dataset,experiments).solve()