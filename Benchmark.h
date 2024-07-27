//
// Created by tudor on 07/01/24.
//

#ifndef C___NSGA_BENCHMARK_H
#define C___NSGA_BENCHMARK_H

#include "Individual.h"
#include <array>
#include <vector>
#include <memory>
#include <unordered_map>

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


    virtual std::array<int, N_OBJECTIVES> getCompute(const std::shared_ptr<Individual> &x) {
        if(cachedCompute.count(x) == 0)
            cachedCompute[x] = compute(*x);
        return cachedCompute[x];
    }

    // Custom hash function
    struct HashFunction {
        std::size_t operator()(const std::array<int, N_OBJECTIVES>& obj) const {
            std::size_t seed = 0;
            for (const int& i : obj) {
                seed ^= std::hash<int>()(i) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            }
            return seed;
        }
    };
private:
    virtual std::array<int, N_OBJECTIVES> compute(const Individual&) = 0;

    std::unordered_map<std::shared_ptr<Individual>, std::array<int, N_OBJECTIVES>> cachedCompute;
};


#endif //C___NSGA_BENCHMARK_H
