//
// Created by Yaser Alkayale on 2017-06-05.
//

#include "csv.h"

namespace kmeans{
//CSVRow stuff
CSVRow::CSVRow() : _data(new std::vector<std::string>()) {}

std::string const &CSVRow::operator[](std::size_t index) const {
  return (*_data)[index];
}

std::size_t CSVRow::size() const {
  return _data->size();
}

void CSVRow::readNextRow(std::istream &str) {
    std::string line;
    std::getline(str, line);

    std::stringstream lineStream(line);
    std::string cell;

    _data->clear();
    while(std::getline(lineStream, cell, ',')) {
        _data->push_back(cell);
    }
    // This checks for a trailing comma with no data after it.
    if(!lineStream && cell.empty()) {
        // If there was a trailing comma then add an empty element.
        _data->push_back("");
    }
}

std::vector<double> CSVRow::toDouble() const {
    std::vector<double> result;

    for(std::string s:*_data) {
        try {
            result.push_back(std::stof(s));
        }
        catch(std::invalid_argument arg) {
            result.clear();
            return result;
        }
    }
    return result;
}

std::istream &operator>>(std::istream &str, CSVRow &data) {
    data.readNextRow(str);
    return str;
}


/*
 * CSVIterator stuff
 */
CSVIterator::CSVIterator(std::istream &str) : m_str(str.good() ? &str : NULL) { ++(*this); }

CSVIterator::CSVIterator() : m_str(NULL) {}


//pre increment
CSVIterator &CSVIterator::operator++() {
    if(m_str) {
        if(!((*m_str) >> m_row)) {
            m_str = NULL;
        }
    }
    return *this;
}

//post increment
CSVIterator CSVIterator::operator++(int) {
    CSVIterator tmp(*this);
    ++(*this);
    return tmp;
}

CSVRow const &CSVIterator::operator*() const { return m_row; }

CSVRow const *CSVIterator::operator->() const { return &m_row; }

bool CSVIterator::operator==(CSVIterator const &rhs) {
    return ((this == &rhs) || ((this->m_str == NULL) && (rhs.m_str == NULL)));
}

bool CSVIterator::operator!=(CSVIterator const &rhs) {
    return !((*this) == rhs);
}

}