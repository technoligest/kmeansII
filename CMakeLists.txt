cmake_minimum_required(VERSION 3.6)
project(kmeansII)

set(CMAKE_CXX_STANDARD 14)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")

find_program( MEMORYCHECK_COMMAND valgrind )
set( MEMORYCHECK_COMMAND_OPTIONS "--trace-children=yes --leak-check=full" )

#set(SOURCE_FILES  lib/main.cc lib/Algorithm/Kmeans.hh lib/handlers/data.hh lib/handlers/dataReader.hh lib/handlers/CSV.hh lib/handlers/CSV.cc lib/Algorithm/KmeansBase.hh  lib/Algorithm/SeedPickers.hh lib/Algorithm/IterationRunners.hh lib/Algorithm/KmeansHelpers.hh lib/Experiments/ExperimentAnalyzer.hh lib/Experiments/experimentsReader.hh lib/Experiments/experimentRunner.hh lib/Experiments/experimentResult.hh)
#add_executable(kmeansII ${SOURCE_FILES})
#
#set(TESTING_SOURCES tests/test-dataReader.cc tests/tests.cc tests/test-CSV.cc tests/test-kmeans.cc tests/test-data.cc lib/handlers/CSV.hh lib/handlers/CSV.cc lib/handlers/data.hh)
#add_executable(testing ${TESTING_SOURCES})
#
#set(TRYING_SOURCES lib/trying.cc lib/trying.hh)
#add_executable(trying ${TRYING_SOURCES})
#
#set(BIG_TEMP_SOURCES lib/main.cc lib/handlers/data.hh lib/Algorithm/Kmeans.hh lib/handlers/CSV.hh lib/handlers/CSV.cc lib/handlers/dataReader.hh lib/handlers/inputArguments.hh lib/Algorithm/IterationRunners.hh lib/Algorithm/SeedPickers.hh lib/Algorithm/SeedPickers.cc lib/Algorithm/IterationRunners.cc lib/Algorithm/KmeansInstance.hh lib/Experiments/experiments.hh lib/Algorithm/Kmeans2Instance.hh lib/Algorithm/LloydIterations.cc lib/Algorithm/LloydIterations.hh lib/Algorithm/IterationRunnerBase.hh lib/Algorithm/LloyIterationRunner.cc lib/Algorithm/LloyIterationRunner.hh lib/Algorithm/LloydIterationRunner.cc lib/Algorithm/LloydIterationRunner.hh)
#add_executable(big_temp ${BIG_TEMP_SOURCES})
#
#set(SMALL_TEMP_SOURCES lib/main.cc lib/handlers/data.hh lib/Algorithm/Kmeans.hh lib/handlers/CSV.hh lib/handlers/CSV.cc lib/handlers/dataReader.hh lib/handlers/inputArguments.hh lib/Algorithm/IterationRunners.hh lib/Algorithm/SeedPickers.hh lib/Algorithm/SeedPickers.cc lib/Algorithm/IterationRunners.cc lib/Algorithm/KmeansInstance.hh lib/Experiments/experiments.hh lib/Algorithm/Kmeans2Instance.hh)
#add_executable(small_temp ${SMALL_TEMP_SOURCES})

file(GLOB tests "${PROJECT_SOURCE_DIR}/tests/*.hh" "${PROJECT_SOURCE_DIR}/tests/*.cc")

file(GLOB algorithm "${PROJECT_SOURCE_DIR}/lib/Algorithm/*.hh" "${PROJECT_SOURCE_DIR}/lib/Algorithm/*.cc")
file(GLOB handlers "${PROJECT_SOURCE_DIR}/lib/handlers/*.hh" "${PROJECT_SOURCE_DIR}/lib/handlers/*.cc")
file(GLOB experiments "${PROJECT_SOURCE_DIR}/lib/Experiments/*.hh" "${PROJECT_SOURCE_DIR}/lib/Experimts/*.cc")

#set(kmeansII main.cc)
set(kmeansII ${algorithm} ${handlers} lib/main.cc)
set(temp ${algorithm} ${handlers} lib/main.cc)
set(trying lib/trying.cc lib/trying.hh)
set(testing tests/test-LloydIterationRunner.cc tests/tests.cc tests/test-kmeansHelpers.cc)
add_executable(kmeansII ${kmeansII})
add_executable(temp ${temp})
add_executable(trying ${trying})
add_executable(testing ${testing})

target_compile_options(testing PUBLIC "-Dprivate=public")

#add_executable(helloworld ${kmeansII})

