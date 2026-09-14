cmake_minimum_required(VERSION 4.3)
project(MatMult VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#find_package(BLAS CONFIG REQUIRED)
#find_package(benchmark REQUIRED)
find_library(BLAS_LIB NAMES openblas PATHS REQUIRED)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_subdirectory(benchmark)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_executable(program program.cpp)

find_path(BLAS_INCLUDE_DIR cblas.h PATH_SUFFIXES openblas REQUIRED)
target_include_directories(program PRIVATE include/ ${BLAS_INCLUDE_DIR})
target_link_libraries(program PRIVATE  ${BLAS_LIB} benchmark::benchmark_main)

enable_testing()
include(GoogleTest)

add_executable(test_kernels test_kernels.cpp)

target_include_directories(test_kernels PRIVATE include/ ${BLAS_INCLUDE_DIR})
target_link_libraries(
  test_kernels
  ${BLAS_LIB}
  GTest::gtest_main
)
gtest_discover_tests(test_kernels)
