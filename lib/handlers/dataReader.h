//
// Created by Yaser Alkayale on 2017-05-29.
//

#ifndef KMEANSII_DATAREADER_H
#define KMEANSII_DATAREADER_H


#include "CSV.h"
#include "data.h"
#include "../pkgs/macro-argparse-plain.hh"

inline Table readFile(std::string fileName) {
    Table t ;
    std::ifstream inputFile(fileName);
    for (CSVIterator it(inputFile); it != CSVIterator(); ++it) {
        t.add(new Row(it->toFloat()));
    }
    return t;
};


Kmeans *readArgs(KmeansArgs args){
    if(args.algorithm=="kmeans"){
        return new Kmeans();
    }
    else if(args.algorithm=="kmenas++"){
        return new Kmeanspp();
    }
    else if(args.algorithm=="kmenasII"){
        return new KmeansII(fabs(args.oversamplingFactor));
    }
    else{
        return NULL;
    }
}
#endif //KMEANSII_DATAREADER_H
