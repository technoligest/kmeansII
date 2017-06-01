#include <iostream>
#include "dataReader.h"
#include "functions.h"
#include "cluster.h"
#include "Kmeans.h"



int main() {
    Table t = readFile("/Users/Technoligest/Documents/Classes/Current/Norbert + Vlado/kmeansII/inputFiles/testingPoints.CSV");

    printTable(t);
    Kmeans k(t, 2);
    k.run();
    auto km = k.getResult();
    for(int i=0; i<km.size(); ++i){
        std::cout<<"\n\nCluster #"<<i+1<<":\n";
        cout<<"The center:\n";
        print(km[i]._center);
        cout<<"\nThe values are:\n";
        printTable(km[i]._values);
    }
    cout<<"Num iterations: \t"<< k.numIterations()<<endl;
    cout<<"Hello";


    return 0;
}




