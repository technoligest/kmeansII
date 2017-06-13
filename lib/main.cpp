
#include "handlers/dataReader.h"
#include "handlers/inputArguments.hh"
#include "Algorithm/Kmeans.h"

using namespace std;

int main(int argc,char** argv) {
  KmeansArgs args;
  if (!args.parse_args(argc, argv)){
    cout<<"Could not parse arguments. Try again."<<endl;
    return 1;
  }
  Kmeans *k = readArgs(args); 
  if(k==NULL){
    cout<<"Could not create Kmeans object. Try again."<<endl;
    return 1;
  }
//    Table t = readFile(
//            "/Users/Technoligest/Documents/Classes/Current/Norbert + Vlado/kmeansII/inputFiles/drivPoints.CSV");
//    cout << t << endl;
//    cout << "The size of the table: " << t.size() << endl;
//    Kmeans *k = new Kmeans(t, 10);
//
//
//    cout << "This should be finished." << endl;
//    cout<<t<<endl;
//    cout<<"The size of the table: "<<t.size()<<endl;
    return 0;
}



//int main() {
//    Table t = readFile(
//            "/Users/Technoligest/Documents/Classes/Current/Norbert + Vlado/kmeansII/inputFiles/drivPoints.CSV");
//    int n = 2; //number of times to run the algorithm
//    Kmeans *k= new Kmeans(t, 10);
////    k.run();
////    auto result = k.getResult();
////    cout << k->sum_squared_distance() << endl;
////    delete k;
////    for (auto i : *result) {
////        std::cout << i << std::endl;
////    }
//    cout << "This should be finished." << endl;
//    return 0;
////    Cluster(new Row());
////    auto i= Table();
//
//////    float totalResult=0;
//////    for(int q=0 ;q<n; q++) {
//////        Kmeanspp k(t, 20);
//////        k.run();
//////        auto km = k.getResult();
//////        float finalResult = 0;
//////        cout<<km->size()<<endl;
//////        for (int i = 0; i < km->size(); ++i) {
////////        std::cout<<"\n\nCluster #"<<i+1<<":\n";
////////        cout<<"The center:\n";
////////        print(km[i]._center);
////////        cout<<"\nThe values are:\n";
////////        printTable(km[i]._values);
////////            cout << "cluster " << i + 1 << " error:" << km[i]._sum_squared_distances << endl;
//////            finalResult += (*km)[i]._sum_squared_distances+1;
//////        }
//////        totalResult+=finalResult;
//////    }
//////    cout<<"Final Result For kmeans++: "<<totalResult/n<<endl;
////////    cout<<"Num iterations: \t"<< k.numIterations()<<endl;
//////
//////
////    for(int q=0 ;q<n; q++) {
////        Kmeans k(t, 10);
////        k.run();
////        auto km = k.getResult();
////
////        float finalResult = 0;
////        for (int i = 0; i < km->size(); ++i) {
//////        std::cout<<"\n\nCluster #"<<i+1<<":\n";
//////        cout<<"The center:\n";
//////        print(km[i]._center);
//////        cout<<"\nThe values are:\n";
//////        printTable(km[i]._values);
//////            cout << "cluster " << i + 1 << " error:" << km[i]._sum_squared_distances << endl;
//////            finalResult += (*km)[i]._sum_squared_distances;
////        }
//////        totalResult+=finalResult;
////    }
//////    cout<<"Final Result For kmeans: "<<totalResult/n<<endl;
//
//}
//
//
//
//
