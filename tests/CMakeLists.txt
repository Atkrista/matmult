find_package(BLAS REQUIRED)
include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY  https://github.com/google/googletest.git
  GIT_TAG 063de7e9578f82b369302001269680b4b1553359 # release-1.18.0
  FIND_PACKAGE_ARGS NAMES GTest
)
FetchContent_MakeAvailable(googletest)

add_executable(matmult_test test_kernels.cpp)
target_link_libraries(matmult_test PRIVATE matmult::matmult BLAS::BLAS GTest::gtest_main)

enable_testing()
include(GoogleTest)
gtest_discover_tests(matmult_test)
