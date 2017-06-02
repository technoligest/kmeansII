cmake_minimum_required(VERSION 3.6)
project(kmeansII)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp Kmeans.cpp Kmeans.h dataReader.h functions.h cluster.h CSV.h Kmeanspp.cpp Kmeanspp.h)
add_executable(kmeansII ${SOURCE_FILES})

set(SOURCE_2 tests/test-dataReader.cpp tests/tests.cpp tests/test-CSV.cpp tests/kmeans.cpp)
add_executable(testing ${SOURCE_2})
