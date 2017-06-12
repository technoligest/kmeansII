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


struct Row {
    Row(std::vector<dataType> dat);
    ~Row();
    std::vector<dataType> data;
    dataType &operator[](std::size_t i);
    void clear();

    size_t size()const;
    bool empty() const;

};

std::ostream &operator<<(std::ostream &, const Row &);

struct Table {
    Table();

    ~Table();

    std::vector<Row> data;

    Row* &operator[](std::size_t i);
    /*
     * Clearing a table removes all of the rows from it; however, it does not free the memory.
     * Once the table is cleared, it is the job of somewhere else to free all the rows.
     */
    void clear();

    /*
     * Pushed a row to the back of the table.
     */
    void add(Row*);
    bool empty() const;
    size_t size()const; //number of rows
};

std::ostream &operator<<(std::ostream &, const Table &);

struct Cluster {
    Table values;
    Row centre;
    float sum_squared_distances;

    Cluster(Row &); //this is the centre of the cluster

    //deleting a cluster does not delete the values in it.
    //That is the job of wherever the values came from
    //this is done for efficiency so no copies of the data needs to be made.
    ~Cluster();

    void resetCentre(); //sets all the centre values to zero
};

std::ostream &operator<<(std::ostream &, const Cluster &);

#endif //KMEANSII_DATA_H