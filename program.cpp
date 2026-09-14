#include "helpers.hpp"
#include "matmult.hpp"
#include <benchmark/benchmark.h>
#include <cstddef>

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

BENCHMARK(BM_sgemm_naive)->RangeMultiplier(2)->Range(64,512)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
