#pragma once
// #include <algorithm>
// #include <iomanip>
// #include <iostream>
#include <random>
#include <vector>

namespace matmult {

// inline void print_histogram(const std::vector<float> &data, float a, float b,
//                             int d) {
//   std::vector<int> counts(d, 0);
//   std::for_each(data.begin(), data.end(), [&](double x) {
//     int idx = std::clamp(static_cast<int>((x - a) / 0.2), 0, d - 1);
//     counts[idx]++;
//   });
//   float start = -1.0;
//   for (auto i = 0; i < counts.size(); ++i)
//     std::cout << std::setw(2) << start << std::string(" to ") << start + i * 0.2
//               << std::string(counts.at(i) / 100, '*') << std::endl;
// }

/**
 * Fill A with reals sampled from a normal distribution with mean 0 and std.
 * dev. 0.2
 **/
template<typename T>
inline void rand_fill(std::vector<T> &A) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::normal_distribution<T> dis(T{}, T{0.2});

  for (auto &x : A)
    x = dis(gen);
}
} // namespace matmult
