//
// Created by Yaser Alkayale on 2017-05-29.
//

#ifndef KMEANSII_DATAREADER_H
#define KMEANSII_DATAREADER_H

#include "functions.h"
#include "CSV.h"

inline Table readFile(string fileName){
    Table _data;
    std::ifstream inputFile(fileName);
    for(CSVIterator it(inputFile); it!=CSVIterator(); ++it) {
        _data.push_back((*it).toFloat());
    }
    return _data;
};


#endif //KMEANSII_DATAREADER_H
