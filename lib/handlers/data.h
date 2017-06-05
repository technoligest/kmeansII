//
// Created by Yaser Alkayale on 2017-06-04.
//



#ifndef KMEANSII_DATA_H
#define KMEANSII_DATA_H

#include <vector>
#include <iostream>

using dataType = float;

class Row;

class Table;

class Cluster;


class Row {
public:
    Row(std::vector<dataType> *dat);
    std::vector<dataType> *data;
};
std::ostream &operator<<(std::ostream &, const Row &);

class Table {
public:
    Table();
    std::vector<Row *> *data;
};
std::ostream &operator<<(std::ostream &, const Table &);

struct Cluster {
    Table _values;
    Row *_center;
    unsigned long _sum_squared_distances;

    Cluster(Table, Row *);

};

std::ostream &operator<<(std::ostream &, const Cluster &);

#endif //KMEANSII_DATA_H