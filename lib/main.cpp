
#include "handlers/dataReader.h"
#include "Algorithm/Kmeans.h"

using namespace std;

int main() {
    Table t = readFile("/Users/Technoligest/Documents/Classes/Current/Norbert + Vlado/kmeansII/inputFiles/drivPoints.CSV");
    int n=2; //number of times to run the algorithm
    cout<<t<<endl;

//    float totalResult=0;
//    for(int q=0 ;q<n; q++) {
//        Kmeanspp k(t, 20);
//        k.run();
//        auto km = k.getResult();
//        float finalResult = 0;
//        cout<<km->size()<<endl;
//        for (int i = 0; i < km->size(); ++i) {
////        std::cout<<"\n\nCluster #"<<i+1<<":\n";
////        cout<<"The center:\n";
////        print(km[i]._center);
////        cout<<"\nThe values are:\n";
////        printTable(km[i]._values);
////            cout << "cluster " << i + 1 << " error:" << km[i]._sum_squared_distances << endl;
//            finalResult += (*km)[i]._sum_squared_distances+1;
//        }
//        totalResult+=finalResult;
//    }
//    cout<<"Final Result For kmeans++: "<<totalResult/n<<endl;
////    cout<<"Num iterations: \t"<< k.numIterations()<<endl;
//
//
    for(int q=0 ;q<n; q++) {
        Kmeans k(t, 10);
        k.run();
        auto km = k.getResult();

        float finalResult = 0;
        for (int i = 0; i < km->size(); ++i) {
//        std::cout<<"\n\nCluster #"<<i+1<<":\n";
//        cout<<"The center:\n";
//        print(km[i]._center);
//        cout<<"\nThe values are:\n";
//        printTable(km[i]._values);
//            cout << "cluster " << i + 1 << " error:" << km[i]._sum_squared_distances << endl;
//            finalResult += (*km)[i]._sum_squared_distances;
        }
//        totalResult+=finalResult;
    }
//    cout<<"Final Result For kmeans: "<<totalResult/n<<endl;
    return 0;
}




