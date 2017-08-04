#!/usr/bin/python
from experiment_instance import ExperimentInstance
class ExperimentAnalyzer:
    def __init__(self, experiments,dataset):
        self.experiments=experiments
        self.dataset = dataset
        print("Created analyzer class")
    # def calcNorbertMatrix(self):
       