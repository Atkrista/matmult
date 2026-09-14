#pragma once
#include <cstddef>

namespace matmult {
/**
 * C := alpha * op(A) * op(B) + beta * C
 * A[m*k]
 * B[k*n]
 * C[m*n]
 * */
static void sgemm_naive(float *A, float *B, float *C, std::size_t m,
                        std::size_t n, std::size_t k) {
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      float acc = 0.0f;
      for (int k1 = 0; k1 < k; ++k1)
        acc += A[i * k + k1] * B[k1 * n + j];
      C[i * n + j] = acc;
    }
  }
}
} // namespace matmult
