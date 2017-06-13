cmake_minimum_required(VERSION 3.6)
project(kmeansII)

set(CMAKE_CXX_STANDARD 14)

find_program( MEMORYCHECK_COMMAND valgrind )
set( MEMORYCHECK_COMMAND_OPTIONS "--trace-children=yes --leak-check=full" )

set(SOURCE_FILES lib/Algorithm/KmeansII.cpp lib/Algorithm/KmeansII.h lib/main.cpp lib/Algorithm/Kmeans.cpp lib/Algorithm/Kmeans.h lib/Algorithm/Kmeanspp.cpp lib/Algorithm/Kmeanspp.h lib/handlers/data.h lib/handlers/data.cpp lib/handlers/dataReader.h lib/handlers/CSV.h lib/handlers/CSV.cpp)
add_executable(kmeansII ${SOURCE_FILES})

set(TESTING_SOURCES tests/test-dataReader.cpp tests/tests.cpp tests/test-CSV.cpp tests/kmeans.cpp tests/test-data.cpp lib/handlers/CSV.h lib/handlers/CSV.cpp lib/handlers/data.h lib/handlers/data.cpp)
add_executable(testing ${TESTING_SOURCES})

set(TRYING_SOURCES lib/trying.cpp lib/trying.h)
add_executable(trying ${TRYING_SOURCES})

#set(TEMP_SOURCES lib/main.cpp lib/handlers/data.h lib/Algorithm/Kmeans.h lib/Algorithm/Kmeans.cpp lib/handlers/CSV.h lib/handlers/dataReader.h lib/handlers/data.cpp)
#add_executable(temp ${TEMP_SOURCES})
