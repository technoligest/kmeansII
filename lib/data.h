//
// Created by Yaser Alkayale on 2017-06-04.
//

#include <vector>

#ifndef KMEANSII_DATA_H
#define KMEANSII_DATA_H



using dataType=float;
class Row;
class Table;
class Cluster;




class Row{
public:
    inline Row(std::vector<dataType>* dat):data(dat){};
    std::vector<dataType>* data;
};
std::ostream& operator<<(std::ostream &outStream, const Row& row){
    for(auto i: *row.data){
        outStream<<i<<"\t";
    }
    return outStream;
}

class Table {
public:
    inline Table():data(new std::vector<Row*>()){}
    std::vector<Row*>* data;

};
std::ostream& operator<<(std::ostream &outStream, const Table& data){
    for(Row *i: *data.data){
        outStream<<(*i)<<"\n";
    }
    return outStream;
}

struct Cluster {
    Table _values;
    Row *_center;
    unsigned long _sum_squared_distances;

    Cluster(Table val, Row *center) : _values(val), _center(center), _sum_squared_distances(0) {};

};

std::ostream& operator<<(std::ostream &outStream, const Cluster& cluster){
    outStream<<"The cluster centre: "<< *cluster._center<<endl;
    outStream<<"The values are: \n"<<cluster._values;
    return outStream;
}



#endif //KMEANSII_DATA_H