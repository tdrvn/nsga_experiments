//
// Created by tudor on 07/01/24.
//

#ifndef C___NSGA_BENCHMARK_H
#define C___NSGA_BENCHMARK_H

#include "Individual.h"
#include <vector>

class Benchmark {
public:
    int fitness_function_calls;
    int n;

    //to debug
    int first_time_inner = -1;

    Benchmark(int _n) : fitness_function_calls(0), n(_n) {}

    virtual bool is_pareto_front_complete(std::vector<Individual> &pop) = 0;

    virtual std::pair<int, int> compute(const Individual&) = 0;

};


#endif //C___NSGA_BENCHMARK_H
