//
// Created by Yaser Alkayale on 2017-05-31.
//
#include "catch.hpp"
#include <fstream>
#include "../lib/algorithm/csv.h"

using namespace std;


TEST_CASE("We can open the file.") {
    std::ifstream inputFile("../tests/input-files/test1.csv");
    REQUIRE(inputFile.good());
};

TEST_CASE("kmeans::CSVRow works properly1") {
    std::ifstream inputFile("../tests/input-files/test1.csv");
    kmeans::CSVRow row;
    inputFile >> row;
    string testArr[] = {"yaser", "alkayale", "is", "the", "best"};
    REQUIRE(row.size() == 5);
};

TEST_CASE("kmeans::CSVRow works properly2") {
    std::ifstream inputFile("../tests/input-files/test1.csv");
    kmeans::CSVRow row;
    inputFile >> row;
    string testArr[] = {"yaser", "alkayale", "is", "the", "best"};


    REQUIRE(row.size() == 5);
    for (int i = 0; i < 5; ++i) {
        REQUIRE(testArr[i] == row[i]);
    }
};

TEST_CASE("Empty CSV row") {
    std::ifstream inputFile("../tests/input-files/empty.csv");
    kmeans::CSVRow row;
    inputFile >> row;

    REQUIRE(row.size() == 1);
    REQUIRE(row[0] == "");
};

TEST_CASE("Multiple Rows in CSV file") {
    std::ifstream inputFile("../tests/input-files/test2.csv");
    kmeans::CSVRow row;

    string testArr[4][2] = {{"1", "a"},
                            {"2", "b"},
                            {"3", "c"},
                            {"4", "d"}};
    for (int i = 0; i < 4; ++i) {
        inputFile >> row;
        REQUIRE(sizeof(testArr[i]) / sizeof(testArr[i][0]) == 2);
        for (int j = 0; j < 2; ++j) {
            REQUIRE(testArr[i][j] == row[j]);
        }
    }
};

TEST_CASE("Converting a row to floats on strings.") {
    std::ifstream inputFile("../tests/input-files/test2.csv");
    kmeans::CSVRow row;
    for (int i = 0; i < 3; ++i) {
        inputFile >> row;
        vector<double> temp = row.toDouble();
        REQUIRE(temp.size() == 0);
    }
};

TEST_CASE("Converting a row to floats.") {
    std::ifstream inputFile("../tests/input-files/test3.csv");
    kmeans::CSVRow row;

    float testArr[3][3] = {{1,    2.1, 5.4},
                           {2.2,  1.4, 5.6},
                           {-2.3, -14, 11}};
    for (int i = 0; i < 3; ++i) {
        inputFile >> row;
        vector<double> temp = row.toDouble();
        REQUIRE(sizeof(testArr[i]) / sizeof(testArr[i][0]) == 3);
        for (int j = 0; j < 3; ++j) {
            REQUIRE(testArr[i][j] == temp[j]);
        }
    }
};

