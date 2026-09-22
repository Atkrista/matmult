#include <matmult/kernels.hpp>
#include "helpers.hpp"
#include <gtest/gtest.h>
#include <vector>
#include <cblas.h>

TEST(SgemmNaive, BasicAssertions) {
  std::size_t m(250), n(255), k(256);
  std::vector<float> A(m*k);
  std::vector<float> B(k*n);
  std::vector<float> C(m*n);
  
  matmult::rand_fill(A);
  matmult::rand_fill(B);

  std::vector<float> C_ref(C);
  cblas_sgemm(CblasRowMajor,
              CblasNoTrans,
              CblasNoTrans,
              m, n, k,
              1.0f,
              A.data(), k,
              B.data(), n,
              0.0f,
              C_ref.data(), n);

  matmult::sgemm_naive(A.data(), B.data(), C.data(), m, n, k);
  
  for (std::size_t i=0; i!=m*n; ++i)
    EXPECT_NEAR(C_ref[i], C[i], 0.001f);
}

TEST(SgemmLoopReorder, BasicAssertions) {
  std::size_t m(250), n(255), k(256);
  std::vector<float> A(m*k);
  std::vector<float> B(k*n);
  std::vector<float> C(m*n);
  
  matmult::rand_fill(A);
  matmult::rand_fill(B);

  std::vector<float> C_ref(C);
  cblas_sgemm(CblasRowMajor,
              CblasNoTrans,
              CblasNoTrans,
              m, n, k,
              1.0f,
              A.data(), k,
              B.data(), n,
              0.0f,
              C_ref.data(), n);

  matmult::sgemm_loopreorder(A.data(), B.data(), C.data(), m, n, k);
  
  for (std::size_t i=0; i!=m*n; ++i)
    EXPECT_NEAR(C_ref[i], C[i], 0.001f);
}
