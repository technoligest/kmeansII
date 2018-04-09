cmake_minimum_required(VERSION 3.6)
project(kmeansII)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -O3")

find_program(MEMORYCHECK_COMMAND valgrind)
set(MEMORYCHECK_COMMAND_OPTIONS "--trace-children=yes --leak-check=full")


file(GLOB tests "${PROJECT_SOURCE_DIR}/tests/*.h" "${PROJECT_SOURCE_DIR}/tests/*.cc")
file(GLOB algorithm "${PROJECT_SOURCE_DIR}/lib/algorithm/*.h" "${PROJECT_SOURCE_DIR}/lib/algorithm/*.cc")
file(GLOB handlers "${PROJECT_SOURCE_DIR}/lib/handlers/*.h" "${PROJECT_SOURCE_DIR}/lib/handlers/*.cc")
file(GLOB experiments "${PROJECT_SOURCE_DIR}/lib/experiments/*.h" "${PROJECT_SOURCE_DIR}/lib/experiments/*.cc")
file(GLOB sideHussle "${PROJECT_SOURCE_DIR}/lib/sidehussle/*.h" "${PROJECT_SOURCE_DIR}/lib/sidehussle/*.cc")
file(GLOB scripts "${PROJECT_SOURCE_DIR}/lib/scripts/*.py")
file(GLOB bigint "lib/sidehussle/bigInt/*.cpp" "lib/sidehussle/bigInt/*.h")
file(GLOB findk "lib/FindK/*.cc" "lib/FindK/*.h")

set(kmeansII ${algorithm} ${handlers})

set(trying ${algorithm} ${handlers} )
set(testing ${tests} ${algorithm} ${handlers} ${experiments} tests/test_experiment_helpers.cc lib/home.h lib/algorithm/globals.h lib/FindK/FindK.cc)

add_executable(findK ${kmeansII} ${findk})
add_executable(kmeans ${kmeansII}  lib/runners/kmeans.cc) #here we can run any of the algorithms from the commandline
add_executable(trying ${trying} lib/runners/trying.cc) #this executable is temporary for development only
add_executable(testing ${testing}) #This executable includes all the testing scripts
add_executable(experiments ${kmeansII} ${experiments} lib/runners/experiment.cc) #this executable helps us run experiments from the commandline

target_link_libraries(trying ${PROJECT_SOURCE_DIR}/lib/scripts/runners/main.py)
target_compile_options(testing PUBLIC "-Dprivate=public")


add_executable(kmeans2 ${kmeansII}  lib/runners/kmeans.cc) #here we can run any of the algorithms from the commandline



