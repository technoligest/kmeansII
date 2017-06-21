//
// Created by Yaser Alkayale on 2017-06-07.
//

//
// Created by Yaser Alkayale on 2017-06-07.
//

#include "catch.hpp"
#include "../lib/handlers/data.h"


//assuming the array is of at least size 1
template<typename T>
std::vector<T> arrayToVector(T t[]) {
    size_t size = sizeof(t) / sizeof(t[0]);
    std::vector<T> result;
    for (int i = 0; i < size; ++i) {
        result.push_back(t[i]);
    }
    return result;
}

TEST_CASE("Row works") {
    std::vector<float> items;
    items.push_back(1.2);
    REQUIRE(items.size() == 1);
    REQUIRE(items[0] - 1.2f < 0.00000001);

    Row r(items);
    REQUIRE(r.size() == 1);
    REQUIRE(!r.empty());
    REQUIRE(r[0] - 1.2f < 0.00000001);

    r[0] = 10.75;
    REQUIRE(r.size() == 1);
    REQUIRE(!r.empty());
    REQUIRE(r[0] - 10.75f < 0.00000001);

    r.clear();
    REQUIRE(r.size() == 0);
    REQUIRE(r.empty());

    items.clear();
    items.push_back(1);
    items.push_back(2.4);
    items.push_back(14.72);
    r = Row(items);

    REQUIRE(r.size() == 3);
    REQUIRE(r[0] - 1 < 0.00001);
    REQUIRE(r[1] - 2.4f < 0.00001);
    REQUIRE(r[2] - 14.72f < 0.00001);

    items.clear();
    r = Row(items);
    REQUIRE(r.size() == 0);
    REQUIRE(r.empty());
    r.clear();
    REQUIRE(r.size() == 0);
    REQUIRE(r.empty());
};

TEST_CASE("Table works0.") {
    Table t;

    REQUIRE(t.size() == 0);
    REQUIRE(t.empty());

    t.clear();
    REQUIRE(t.size() == 0);
    REQUIRE(t.empty());
    std::vector<float> *i1 = new std::vector<float>();
    i1->push_back(1);
    std::vector<float> *i2 = new std::vector<float>();
    i2->push_back(2);
    std::vector<float> *i3 = new std::vector<float>();
    i3->push_back(3);
    Row *r1 = new Row(*i1);
    Row *r2 = new Row(*i2);
    Row *r3 = new Row(*i3);
    t.add(r1);
    t.add(r2);
    t.add(r3);

    REQUIRE(t.size() == 3);
    REQUIRE(!t.empty());

    REQUIRE(t[0] == r1);
    REQUIRE(t[1] == r2);
    REQUIRE(t[2] == r3);

    t[1] = r1;
    REQUIRE(t[1] == r1);
    t[2] = r1;
    REQUIRE(t[2] == r1);

    t[0] = r1;
    t[1] = r2;
    t[2] = r3;
}

TEST_CASE("Table works.") {
    Table t;

    REQUIRE(t.size() == 0);
    REQUIRE(t.empty());

    t.clear();
    REQUIRE(t.size() == 0);
    REQUIRE(t.empty());
    std::vector<float> i1;
    i1.push_back(1);
    std::vector<float> i2;
    i2.push_back(2);
    std::vector<float> i3;
    i3.push_back(3);
    Row *r1 = new Row(i1);
    Row *r2 = new Row(i2);
    Row *r3 = new Row(i3);
    t.add(r1);
    t.add(r2);
    t.add(r3);

    REQUIRE(t.size() == 3);
    REQUIRE(!t.empty());

    REQUIRE(t[0] == r1);
    REQUIRE(t[1] == r2);
    REQUIRE(t[2] == r3);

    t[1] = r1;
    REQUIRE(t[1] == r1);

    t.clear();
    REQUIRE(t.size() == 0);
    REQUIRE(t.empty());

}

TEST_CASE("Cluster works.") {
    Table t;
    std::vector<float> i1;
    i1.push_back(1);
    std::vector<float> i2;
    i2.push_back(2);
    std::vector<float> i3;
    i3.push_back(3);
    std::vector<float> i4;
    i4.push_back(4);
    Row *r1 = new Row(i1);
    Row *r2 = new Row(i2);
    Row *r3 = new Row(i3);
    Row *r4 = new Row(i4);
    t.add(r1);
    t.add(r2);
    t.add(r3);

    Cluster c(*r4);
    c.sum_squared_distances = 10.5;
    REQUIRE(c.sum_squared_distances - 10.5f < 0.000001);

    c.values = t;
    REQUIRE(&c.values!=&t);

//    delete r4;
//    r4= new Row();

    //making sure everything will be deleted properly
    delete r4;
    t[0] = r1;
    t[1] = r2;
    t[2] = r3;
}