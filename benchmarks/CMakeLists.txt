include(FetchContent)
FetchContent_Declare(
  benchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG 192ef10025eb2c4cdd392bc502f0c852196baa48 # release-1.9.5
  FIND_PACKAGE_ARGS NAMES benchmark
)
FetchContent_MakeAvailable(benchmark)
add_executable(matmult_bench bench_kernels.cpp)
target_link_libraries(matmult_bench PRIVATE matmult::matmult benchmark::benchmark_main)
