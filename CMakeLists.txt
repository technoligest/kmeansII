cmake_minimum_required(VERSION 3.6)
project(kmeansII)

set(CMAKE_CXX_STANDARD 14)

find_program( MEMORYCHECK_COMMAND valgrind )
set( MEMORYCHECK_COMMAND_OPTIONS "--trace-children=yes --leak-check=full" )

set(SOURCE_FILES  lib/main.cc lib/Algorithm/Kmeans.hh lib/handlers/data.hh lib/handlers/dataReader.hh lib/handlers/CSV.hh lib/handlers/CSV.cc lib/Algorithm/KmeansBase.hh  lib/Algorithm/SeedPickers.hh lib/Algorithm/IterationRunners.hh lib/Algorithm/KmeansHelpers.hh lib/Experiments/ExperimentAnalyzer.hh lib/Experiments/experimentsReader.hh lib/Experiments/experimentRunner.hh lib/Experiments/experimentResult.hh)
add_executable(kmeansII ${SOURCE_FILES})

set(TESTING_SOURCES tests/test-dataReader.cc tests/tests.cc tests/test-CSV.cc tests/test-kmeans.cc tests/test-data.cc lib/handlers/CSV.hh lib/handlers/CSV.cc lib/handlers/data.hh)
add_executable(testing ${TESTING_SOURCES})

set(TRYING_SOURCES lib/trying.cc lib/trying.hh)
add_executable(trying ${TRYING_SOURCES})

set(TEMP_SOURCES lib/main.cc lib/handlers/data.hh lib/Algorithm/Kmeans.hh lib/handlers/CSV.hh lib/handlers/CSV.cc lib/handlers/dataReader.hh lib/handlers/inputArguments.hh lib/Algorithm/IterationRunners.hh lib/Algorithm/SeedPickers.hh lib/Algorithm/SeedPickers.cc lib/Algorithm/IterationRunners.cc lib/Algorithm/KmeansInstance.hh lib/Experiments/experiments.hh lib/Algorithm/Kmeans2Instance.hh)
add_executable(temp ${TEMP_SOURCES})
