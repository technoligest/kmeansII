cmake_minimum_required(VERSION 3.6)
project(kmeansII)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES lib/main.cpp lib/Kmeans.cpp lib/Kmeans.h lib/Kmeanspp.cpp lib/Kmeanspp.h lib/data.h lib/dataReader.h lib/CSV.h)
add_executable(kmeansII ${SOURCE_FILES})

set(TESTING_SOURCES tests/test-dataReader.cpp tests/tests.cpp tests/test-CSV.cpp tests/kmeans.cpp)
add_executable(testing ${TESTING_SOURCES})

set(TRYING_SOURCES lib/trying.cpp lib/trying.h)
add_executable(trying ${TRYING_SOURCES})

set(TEMP_SOURCES lib/main.cpp lib/data.h lib/Kmeans.h lib/Kmeans.cpp)
add_executable(temp ${TEMP_SOURCES})
