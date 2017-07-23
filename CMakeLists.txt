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
set(trying ${experiments} ${algorithm} ${handlers} lib/trying.cc lib/trying.h lib/experiments/experiment_analyzer2.cc lib/experiments/experiment_analyzer2.h)
set(testing ${tests} ${algorithm} ${handlers} ${experiments} )

add_executable(kmeansII ${kmeansII} lib/main.cc)
add_executable(trying ${trying} lib/experiments/experiment_helpers.cc lib/experiments/experiment_runner.cc lib/experiments/experiments_reader.cc)
add_executable(testing ${testing})

add_executable(fuckThis ${algorithm} ${handlers} ${experiments} lib/trying.cc lib/experiments/experiments_reader.cc)
target_compile_options(testing PUBLIC "-Dprivate=public")



file(GLOB sideHussle "${PROJECT_SOURCE_DIR}/lib/sidehussle/*.h" "${PROJECT_SOURCE_DIR}/lib/sidehussle/*.cc")
add_executable(sideHussle ${sideHussle} lib/sidehussle/main.cc)
