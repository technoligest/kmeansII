
#include <iostream>
#include <fstream>
#include <sstream>
#include "handlers/data.h"

using namespace std;

int main(int argc, char **argv) {
    Dataset d =readFile("/Users/Technoligest/Documents/Classes/Current/Norbert + Vlado/kmeansII/inputFiles/DimREdFullData.txt");
    cout<<d<<endl;
    return 0;
}