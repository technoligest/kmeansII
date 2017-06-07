//
// Created by Yaser Alkayale on 2017-05-29.
//

#ifndef KMEANSII_DATAREADER_H
#define KMEANSII_DATAREADER_H


#include "CSV.h"
#include "data.h"

inline Table readFile(std::string fileName) {
    Table t ;
    std::ifstream inputFile(fileName);
    for (CSVIterator it(inputFile); it != CSVIterator(); ++it) {
        t.add(new Row(*(*it).toFloat()));
    }
    return t;
};


#endif //KMEANSII_DATAREADER_H
