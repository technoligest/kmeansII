cmake_minimum_required(VERSION 3.6)
project(kmeansII)

set(CMAKE_CXX_STANDARD 14)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")

find_program( MEMORYCHECK_COMMAND valgrind )
set( MEMORYCHECK_COMMAND_OPTIONS "--trace-children=yes --leak-check=full" )

#set(SOURCE_FILES  lib/main.cc lib/algorithm/Kmeans.hh lib/handlers/data.hh lib/handlers/dataReader.hh lib/handlers/CSV.hh lib/handlers/CSV.cc lib/algorithm/KmeansBase.hh  lib/algorithm/SeedPickers.hh lib/algorithm/IterationRunners.hh lib/algorithm/KmeansHelpers.hh lib/experiments/ExperimentAnalyzer.hh lib/experiments/experimentsReader.hh lib/experiments/experimentRunner.hh lib/experiments/experimentResult.hh)
#add_executable(kmeansII ${SOURCE_FILES})

file(GLOB tests "${PROJECT_SOURCE_DIR}/tests/*.h" "${PROJECT_SOURCE_DIR}/tests/*.cc")

file(GLOB algorithm "${PROJECT_SOURCE_DIR}/lib/algorithm/*.h" "${PROJECT_SOURCE_DIR}/lib/algorithm/*.cc")
file(GLOB handlers "${PROJECT_SOURCE_DIR}/lib/handlers/*.h" "${PROJECT_SOURCE_DIR}/lib/handlers/*.cc")
file(GLOB experiments "${PROJECT_SOURCE_DIR}/lib/experiments/*.h" "${PROJECT_SOURCE_DIR}/lib/experiments/*.cc")

set(kmeansII ${algorithm} ${handlers})
set(trying ${experiments} ${algorithm} ${handlers} lib/trying.cc lib/trying.h)
set(testing tests/test_lloyd_iteration_runner.cc tests/tests.cc tests/test_kmeans_helpers.cc lib/algorithm/lloyd_iteration_runner.cc lib/algorithm/kmeans_data.cc lib/algorithm/kmeans_helpers.cc tests/test_kmeans_data.cc)

add_executable(kmeansII ${kmeansII} lib/main.cc)
add_executable(trying ${trying} lib/experiments/experiment_helpers.cc lib/experiments/experiment_runner.cc)
add_executable(testing ${testing})

add_executable(fuckThis ${algorithm} ${handlers} ${experiments} lib/trying.cc)
target_compile_options(testing PUBLIC "-Dprivate=public")


