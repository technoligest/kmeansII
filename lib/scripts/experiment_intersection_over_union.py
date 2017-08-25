from experiment_distances import findBelongingCentrePosition, findDistanceMatrix
from experiment_io import minimum_weight_perfect_matching


class calcIntersections:
  def calcNorbertArray(self):
    for i in range(1, len(self.experiments)):
      self.experiment[i].centres = [self.experiments[i].centres[x] for x, _ in minimum_weight_perfect_matching(
        findDistanceMatrix(self.experiments[0].centres, self.experiments[i].centres))]
    return [[findBelongingCentrePosition(self.dataset[instId], self.experiments[experimentId].centres) for instId in
             range(len(self.dataset))] for experimentId in range(len(self.experiments))]

  def __init__(self, dataset, experiments):
    self.dataset = dataset
    self.experiments = experiments
    self.norbertArray = self.calcNorbertArray()


def calcIntersectionOverUnion(dataset, experiments):
  return calcIntersections(dataset, experiments).solve()
