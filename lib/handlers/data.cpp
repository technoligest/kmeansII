//
// Created by Yaser Alkayale on 2017-06-05.
//
#include "data.h"

Row::Row(std::vector<dataType> *dat) : data(dat) {};

std::ostream &operator<<(std::ostream &outStream, const Row &row) {
    for (auto i: *(row.data)) {
        outStream << i << "\t";
    }
    return outStream;
}

Table::Table() : data(new std::vector<Row *>()) {};

std::ostream &operator<<(std::ostream &outStream, const Table &data) {
    for (Row *i: *data.data) {
        outStream << *i << "\n";
    }
    return outStream;
}

Cluster::Cluster(Table val, Row *center) : _values(val), _center(center), _sum_squared_distances(0) {};

std::ostream &operator<<(std::ostream &outStream, const Cluster &cluster) {
    outStream << "The cluster centre: " << *cluster._center << std::endl;
    outStream << "The values are: \n" << cluster._values;
    return outStream;
}