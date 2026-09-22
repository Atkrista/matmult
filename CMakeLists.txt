cmake_minimum_required(VERSION 4.3)
project(MatMult VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-O2 -march=native")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(MATMULT_BUILD_TESTS "Build tests" ${PROJECT_IS_TOP_LEVEL})
option(MATMULT_BUILD_BENCHMARKS "Build tests" ${PROJECT_IS_TOP_LEVEL})

add_library(matmult INTERFACE)
add_library(matmult::matmult ALIAS matmult)

target_include_directories(matmult INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

if(MATMULT_BUILD_TESTS OR MATMULT_BUILD_BENCHMARKS)
  add_subdirectory(helpers)
endif()

if(MATMULT_BUILD_TESTS)
  add_subdirectory(tests)
endif()

if(MATMULT_BUILD_BENCHMARKS)
  add_subdirectory(benchmarks)
endif()
