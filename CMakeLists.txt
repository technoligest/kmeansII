cmake_minimum_required(VERSION 3.6)
project(kmeansII)

set(CMAKE_CXX_STANDARD 17)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

find_program( MEMORYCHECK_COMMAND valgrind )
set( MEMORYCHECK_COMMAND_OPTIONS "--trace-children=yes --leak-check=full" )


file(GLOB tests "${PROJECT_SOURCE_DIR}/tests/*.h" "${PROJECT_SOURCE_DIR}/tests/*.cc")
file(GLOB algorithm "${PROJECT_SOURCE_DIR}/lib/algorithm/*.h" "${PROJECT_SOURCE_DIR}/lib/algorithm/*.cc")
file(GLOB handlers "${PROJECT_SOURCE_DIR}/lib/handlers/*.h" "${PROJECT_SOURCE_DIR}/lib/handlers/*.cc")
file(GLOB experiments "${PROJECT_SOURCE_DIR}/lib/experiments/*.h" "${PROJECT_SOURCE_DIR}/lib/experiments/*.cc")
file(GLOB sideHussle "${PROJECT_SOURCE_DIR}/lib/sidehussle/*.h" "${PROJECT_SOURCE_DIR}/lib/sidehussle/*.cc")
file(GLOB scripts "${PROJECT_SOURCE_DIR}/lib/scripts/*.py")
file(GLOB bigint "${PROJECT_SOURCE_DIR}/lib/bigInt/*.cpp" "${PROJECT_SOURCE_DIR}/lib/bigInt/*.h")

set(kmeansII ${algorithm} ${handlers} lib/bigInt/big_int.cpp lib/bigInt/big_int.h lib/bigInt/main.cpp)

set(trying ${experiments} ${algorithm} ${handlers})
set(testing ${tests} ${algorithm} ${handlers} ${experiments} tests/test_experiment_helpers.cc)

add_executable(kmeansII ${kmeansII} ${experiments} lib/main.cc)
add_executable(trying ${trying} ${bigint} lib/trying.cc)
add_executable(testing ${testing})
add_executable(sideHussle ${sideHussle} lib/sidehussle/main.cc)


target_link_libraries(trying ${PROJECT_SOURCE_DIR}/lib/scripts/runners/main.py)
target_compile_options(testing PUBLIC "-Dprivate=public")



