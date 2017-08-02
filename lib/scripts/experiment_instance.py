#!/usr/bin/python
import sys

class ExperimentInstance: 
    def init():
        print("yaay")
    def centresToString(self):
        result= ""
        for inst in self.centres:
            result+=str(inst[0])+" "+str(inst[1])+"\n"
        return result;
    def __str__(self):
        return (">>>Start Experiment\n"+
                "algorithm:"+self.algorithm+"\n"
                "Sum of distance squared to centre:"+str(self.distanceToCentre)+"\n"+
                "Time to pick the seeds:"+str(self.timeToPickSeeds)+"\n"+
                "Number of iterations run:"+str(self.numIterations)+"\n"+
                "Time to run the iterations:"+str(self.timeToRunIterations)+"\n"+
                "Start Centres:\n"+ self.centresToString()+
                "End Centres:\n"+ 
                "End Experiment:"
                )
def readCentres(file):
    centres = []
    for line in file:
        if line[:11]=="End Centres":
            break
        temp = line.strip().split()
        centres.append([float(temp[0]), float(temp[1])])
    return centres
def readExperiment(file):
    result=ExperimentInstance()
    for inputLine in file:
        line = inputLine.strip().split(":")
        print(line)
        if len(line)==0:
            continue
        elif line[0] == "Start Centres":
            result.centres=readCentres(file)
        elif line[0] =="End Experiment":
            return result
        elif line[0]=="algorithm":
            result.algorithm=line[1]
        elif line[0]=="Sum of distance squared to centre":
            result.distanceToCentre=float(line[1])
        elif line[0]=="Time to pick the seeds":
            result.timeToPickSeeds = float(line[1])
        elif line[0]=="Number of iterations run":
            result.numIterations = int(line[1])
        elif line[0]=="Time to run the iterations":
            result.timeToRunIterations = float(line[1])
    return None
             
def readExperiments(fileName):
    with open(fileName) as file:
        result =[]
        while True:
            temp = readExperiment(file)
            if temp == None:
                return result
            result.append(temp)
v = readExperiments(sys.argv[1])
print(len(v))
print(v[0].distanceToCentre)
# for i in v:
    # print( str(i) + " ")
for i in range(len(v)):
    print(i,v[i])       

       