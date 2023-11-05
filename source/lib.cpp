#include "lib.hpp"

#include <algorithm>
#include <cmath>
#include <chrono>
#include <execution>
#include <iostream>
#include <tbb/parallel_for.h>
#include <vector>

const size_t N = 1000000;

double std_for() {
  auto values = std::vector<double>(N);

  size_t n_par = 5lu;
  auto indices = std::vector<size_t>(n_par);
  std::iota(indices.begin(), indices.end(), 0lu);
  size_t stride = static_cast<size_t>(N / n_par) + 1;

  std::for_each(
      std::execution::par,
      indices.begin(),
      indices.end(),
      [&](size_t index) {
        int begin = index * stride;
        int end = (index+1) * stride;
        for (int i = begin; i < end; ++i) {
          values[i] = 1.0 / (1 + std::exp(-std::sin(i * 0.001)));
        }
      });

  double total = 0;

  for (double value : values)
  {
    total += value;
  }
  return total;
}

double tbb_for() {
  auto values = std::vector<double>(N);

  tbb::parallel_for(
      tbb::blocked_range<int>(0, values.size()),
      [&](tbb::blocked_range<int> r) {
        for (int i=r.begin(); i<r.end(); ++i) {
          values[i] = 1.0 / (1 + std::exp(-std::sin(i * 0.001)));
        }
      });

  double total = 0;
  for (double value : values) {
    total += value;
  }
  return total;
}

double omp_for()
{
  auto values = std::vector<double>(N);

#pragma omp parallel for
  for (int i=0; i<values.size(); ++i) {
    values[i] = 1.0 / (1 + std::exp(-std::sin(i * 0.001)));
  }

  double total = 0;

  for (double value : values) {
    total += value;
  }
  return total;
}

double seq_for()
{
  auto values = std::vector<double>(N);

  for (int i=0; i<values.size(); ++i) {
    values[i] = 1.0 / (1 + std::exp(-std::sin(i * 0.001)));
  }

  double total = 0;

  for (double value : values) {
    total += value;
  }
  return total;
}

void time_it(double(*fn_ptr)(), const std::string& fn_name) {
  auto t1 = std::chrono::high_resolution_clock::now();
  auto rez = fn_ptr();
  auto t2 = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
  std::cout << fn_name << ", rez = " << rez << ", dur = " << duration << std::endl;
}

library::library()
    : name {"threading"}
{
}

int library::run(std::string & op) {
  if (op == "std_for") {
    time_it(&std_for, op);
  } else if (op == "omp_for") {
    time_it(&omp_for, op);
  } else if (op == "tbb_for") {
    time_it(&tbb_for, op);
  } else if (op == "seq_for") {
    time_it(&seq_for, op);
  }
  return 0;
}