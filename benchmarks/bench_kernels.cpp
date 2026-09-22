#include "helpers.hpp"
#include "matmult.hpp"
#include <benchmark/benchmark.h>
#include <cstddef>

static void BM_sgemm_cblas(benchmark::State &state) {
  const std::size_t n = state.range(0);

  std::vector<float> A(n*n);
  std::vector<float> B(n*n);
  std::vector<float> C(n*n);
  matmult::rand_fill(A);
  matmult::rand_fill(B);
  
  for (auto _ : state) {
  cblas_sgemm(CblasRowMajor,
              CblasNoTrans,
              CblasNoTrans,
              n, n, n,
              1.0f,
              A.data(), n,
              B.data(), n,
              0.0f,
              C.data(), n);
    benchmark::DoNotOptimize(C);
  }

  const double FLOPS = 2.0 * n * n *n;
  state.counters["GFLOPS"] = benchmark::Counter(FLOPS, benchmark::Counter::kIsIterationInvariantRate,
      benchmark::Counter::OneK::kIs1000);
}

static void BM_sgemm_naive(benchmark::State &state) {
  const std::size_t n = state.range(0);

  std::vector<float> A(n*n);
  std::vector<float> B(n*n);
  std::vector<float> C(n*n);
  matmult::rand_fill(A);
  matmult::rand_fill(B);
  
  for (auto _ : state) {
    matmult::sgemm_naive(A.data(), B.data(), C.data(), n, n, n);
    benchmark::DoNotOptimize(C);
  }

  const double FLOPS = 2.0 * n * n *n;
  state.counters["GFLOPS"] = benchmark::Counter(FLOPS, benchmark::Counter::kIsIterationInvariantRate,
      benchmark::Counter::OneK::kIs1000);
}

static void BM_sgemm_loopreorder(benchmark::State &state) {
  const std::size_t n = state.range(0);

  std::vector<float> A(n*n);
  std::vector<float> B(n*n);
  std::vector<float> C(n*n);
  matmult::rand_fill(A);
  matmult::rand_fill(B);
  
  for (auto _ : state) {
    matmult::sgemm_loopreorder(A.data(), B.data(), C.data(), n, n, n);
    benchmark::DoNotOptimize(C);
  }

  const double FLOPS = 2.0 * n * n *n;
  state.counters["GFLOPS"] = benchmark::Counter(FLOPS, benchmark::Counter::kIsIterationInvariantRate,
      benchmark::Counter::OneK::kIs1000);
}
BENCHMARK(BM_sgemm_cblas)->RangeMultiplier(2)->Range(64, 8192)->Unit(benchmark::kMillisecond);
BENCHMARK(BM_sgemm_naive)->RangeMultiplier(2)->Range(64, 1024)->Unit(benchmark::kMillisecond);
BENCHMARK(BM_sgemm_loopreorder)->RangeMultiplier(2)->Range(64, 8192)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
