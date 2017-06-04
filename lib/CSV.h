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
    inline std::string const &operator[](std::size_t index) const {
        return (*_data)[index];
    }

    inline std::size_t size() const {
        return _data->size();
    }

    inline void readNextRow(std::istream &str) {
        std::string line;
        std::getline(str, line);

        std::stringstream lineStream(line);
        std::string cell;

        _data->clear();
        while (std::getline(lineStream, cell, ',')) {
            _data->push_back(cell);
        }
        // This checks for a trailing comma with no data after it.
        if (!lineStream && cell.empty()) {
            // If there was a trailing comma then add an empty element.
            _data->push_back("");
        }
    }

    inline std::vector<float>* toFloat() const {
        std::vector<float>* result= new std::vector<float>();

        for (std::string s:*_data) {
            try {
                result->push_back(std::stof(s));
            }
            catch(std::invalid_argument arg){
                result->clear();
                return result;
            }
        }
        return result;
    }

private:
    std::vector<std::string>* _data = new std::vector<std::string>();
};

std::istream &operator>>(std::istream &str, CSVRow &data) {
    data.readNextRow(str);
    return str;
}

class CSVIterator {
public:
    typedef std::input_iterator_tag iterator_category;
    typedef CSVRow value_type;
    typedef std::size_t difference_type;
    typedef CSVRow *pointer;
    typedef CSVRow &reference;

    CSVIterator(std::istream &str) : m_str(str.good() ? &str : NULL) { ++(*this); }

    CSVIterator() : m_str(NULL) {}

    // Pre Increment
    CSVIterator &operator++() {
        if (m_str) {
            if (!((*m_str) >> m_row)) {
                m_str = NULL;
            }
        }
        return *this;
    }

    // Post increment
    CSVIterator operator++(int) {
        CSVIterator tmp(*this);
        ++(*this);
        return tmp;
    }

    CSVRow const &operator*() const { return m_row; }

    CSVRow const *operator->() const { return &m_row; }

    bool operator==(CSVIterator const &rhs) {
        return ((this == &rhs) || ((this->m_str == NULL) && (rhs.m_str == NULL)));
    }

    bool operator!=(CSVIterator const &rhs) { return !((*this) == rhs); }

private:
    std::istream *m_str;
    CSVRow m_row;
};


#endif //KMEANSII_CSV_H
