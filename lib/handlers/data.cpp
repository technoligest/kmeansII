//
// Created by Yaser Alkayale on 2017-06-05.
//
#include "data.h"

Row::Row(std::vector<dataType> dat) : data(dat) {};

Row::~Row() {
    std::cout << "Deleting row " << std::endl;
}

dataType &Row::operator[](std::size_t i) {
    return data[i];
}

void Row::clear() {
    data.clear();
}

size_t Row::size() const {
    return data.size();
}

bool Row::empty() const {
    return data.empty();
}

std::ostream &operator<<(std::ostream &outStream, const Row &row) {
    for (auto i: row.data) {
        outStream << i << "\t";
    }
    return outStream;
}

Table::Table() {};

Table::~Table() {
    std::cout << "deleting table." << std::endl;
    for (Row *row:data) {
        delete row;
    }
    std::cout << "finished deleting table" << std::endl;
}

void Table::add(Row *r) {
    data.push_back(r);
}

bool Table::empty() const {
    return data.empty();
}

size_t Table::size() const {
    return data.size();
}

Row *&Table::operator[](std::size_t i) {
    return data[i];
};

void Table::clear() {
    data.clear();
}

std::ostream &operator<<(std::ostream &outStream, const Table &data) {
    for (Row *i: data.data) {
        outStream << *i << "\n";
    }
    return outStream;
}

Cluster::Cluster(Row &c) : centre(c), sum_squared_distances(0) {};

Cluster::~Cluster() {
    values.clear();
//    std::cout<<"deleting cluster"<<std::endl;
}

void Cluster::resetCentre() {
    for (int i = 0; i < centre.data.size(); ++i) {
        centre[i] = 0;
    }
}

std::ostream &operator<<(std::ostream &outStream, const Cluster &cluster) {
    outStream << "The cluster centre: " << cluster.centre << std::endl;
    outStream << "The values are: \n" << cluster.values;
    return outStream;
}