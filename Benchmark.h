//
// Created by tudor on 07/01/24.
//

#ifndef C___NSGA_BENCHMARK_H
#define C___NSGA_BENCHMARK_H

#include "Individual.h"
#include <array>
#include <vector>
#include <memory>

template <std::size_t N_OBJECTIVES>
class Benchmark {
public:
    long long fitness_function_calls = 0;
    int n;
    int k = 0;

    //to debug
    int first_time_inner = -1;

    Benchmark(int _n) : n(_n) {}

    virtual bool is_pareto_front_complete(const std::vector<std::shared_ptr<Individual>> &pop) = 0;

    virtual std::array<int, N_OBJECTIVES> compute(const Individual&) = 0;

};


#endif //C___NSGA_BENCHMARK_H
