add_library(matmult_helpers STATIC src/helpers.cpp)
add_library(matmult::helpers ALIAS matmult_helpers)

target_include_directories(matmult_helpers PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(matmult_helpers PUBLIC matmult::matmult)
