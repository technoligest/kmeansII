cmake_minimum_required(VERSION 3.6)
project(kmeansII)

set(CMAKE_CXX_STANDARD 14)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

find_program( MEMORYCHECK_COMMAND valgrind )
set( MEMORYCHECK_COMMAND_OPTIONS "--trace-children=yes --leak-check=full" )


file(GLOB tests "${PROJECT_SOURCE_DIR}/tests/*.h" "${PROJECT_SOURCE_DIR}/tests/*.cc")
file(GLOB algorithm "${PROJECT_SOURCE_DIR}/lib/algorithm/*.h" "${PROJECT_SOURCE_DIR}/lib/algorithm/*.cc")
file(GLOB handlers "${PROJECT_SOURCE_DIR}/lib/handlers/*.h" "${PROJECT_SOURCE_DIR}/lib/handlers/*.cc")
file(GLOB experiments "${PROJECT_SOURCE_DIR}/lib/experiments/*.h" "${PROJECT_SOURCE_DIR}/lib/experiments/*.cc")
file(GLOB sideHussle "${PROJECT_SOURCE_DIR}/lib/sidehussle/*.h" "${PROJECT_SOURCE_DIR}/lib/sidehussle/*.cc")

set(kmeansII ${algorithm} ${handlers})
set(trying ${experiments} ${algorithm} ${handlers})
set(testing ${tests} ${algorithm} ${handlers} ${experiments} tests/test_experiment_helpers.cc)

add_executable(kmeansII ${kmeansII} ${experiments} lib/main.cc)
add_executable(trying ${trying} lib/trying.cc)
add_executable(testing ${testing})
add_executable(sideHussle ${sideHussle} lib/sidehussle/main.cc)


target_compile_options(testing PUBLIC "-Dprivate=public")



