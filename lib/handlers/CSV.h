//
// Created by Yaser Alkayale on 2017-05-31.
//

#ifndef KMEANSII_CSV_H
#define KMEANSII_CSV_H


#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

class CSVRow {
public:
    CSVRow();
    std::string const &operator[](std::size_t)const;
    std::size_t size()const;
    void readNextRow(std::istream &);
    std::vector<double> toFloat() const;

private:
    std::vector<std::string>* _data;
};

std::istream &operator>>(std::istream &, CSVRow &);

class CSVIterator {
public:
    typedef std::input_iterator_tag iterator_category;
    typedef CSVRow value_type;
    typedef std::size_t difference_type;
    typedef CSVRow *pointer;
    typedef CSVRow &reference;

    CSVIterator(std::istream &);
    CSVIterator();


    CSVIterator &operator++();   // Pre Increment
    CSVIterator operator++(int); // Post increment

    CSVRow const &operator*() const;
    CSVRow const *operator->() const;

    bool operator==(CSVIterator const &);
    bool operator!=(CSVIterator const &);

private:
    std::istream *m_str;
    CSVRow m_row;
};


#endif //KMEANSII_CSV_H
