//
// Created by Yaser Alkayale on 2017-06-07.
//

#include "catch.hpp"
#include "../lib/handlers/data.h"

TEST_CASE("We can open the file.") {

    std::ifstream inputFile("../tests/input-files/test1.csv");
    REQUIRE(inputFile.good());
}