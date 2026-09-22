#pragma once
#include <cstddef>
#include <mdspan>

namespace matmult {
/**
 * C := alpha * op(A) * op(B) + beta * C
 * A[m*k]
 * B[k*n]
 * C[m*n]
 * */
inline void sgemm_naive(float *A, float *B, float *C, std::size_t m,
                        std::size_t n, std::size_t k) {
  auto msA = std::mdspan(A, m, k);
  auto msB = std::mdspan(B, k, n);
  auto msC = std::mdspan(C, m, n);

  for (size_t i = 0; i != msC.extent(0); ++i) {
    for (size_t j = 0; j != msC.extent(1); ++j) {
      float acc = 0.0f;
      for (size_t k1 = 0; k1 != msB.extent(0); ++k1) {
        acc += msA[i,k1] * msB[k1, j];
      }
      msC[i, j] = acc;
    }
  }
}

inline void sgemm_loopreorder(float *A, float *B, float *C, std::size_t m,
                        std::size_t n, std::size_t k) {
  auto msA = std::mdspan(A, m, k);
  auto msB = std::mdspan(B, k, n);
  auto msC = std::mdspan(C, m, n);

  for (size_t i = 0; i != msC.extent(0); ++i) {
    for (size_t k1 = 0; k1 != msB.extent(0); ++k1){
      for (size_t j = 0; j != msC.extent(1); ++j) {
        msC[i, j] += msA[i,k1] * msB[k1, j];
      }
    }
  }
}
} // namespace matmult
