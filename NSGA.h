#ifndef C___NSGA_NSGA_H
#define C___NSGA_NSGA_H

#include "Benchmark.h"
#include "Individual.h"
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <limits>
#include <map>

using namespace std;
template <typename T>
std::vector<T> operator+(std::vector<T> const &x, std::vector<T> const &y)
{
    std::vector<T> vec;
    vec.reserve(x.size() + y.size());
    vec.insert(vec.end(), x.begin(), x.end());
    vec.insert(vec.end(), y.begin(), y.end());
    return vec;
}

template <typename T>
std::vector<T> &operator+=(std::vector<T> &x, const std::vector<T> &y)
{
    x.reserve(x.size() + y.size());
    x.insert(x.end(), y.begin(), y.end());
    return x;
}



class NSGA {
public:
    Benchmark &f;
    vector<Individual> pop;
    int POP_SIZE;
// to debug
    int iter_reach_inner = -1;

    NSGA(int n, int population_size, Benchmark &bench): POP_SIZE(population_size), f(bench){
        for(int i = 0; i< POP_SIZE; i++){
            Individual x(n);
            x.initialize_individual();
            pop.push_back(x);
        }
    }

    /**
     * @return For each value the individuals with that rank.
     */
    map<int, vector<Individual> > non_dominated_sort(const vector<Individual> &res);

    /**
     *
     * @param res
     * @return Computes in the same order.
     */
    vector<double> compute_crowding_distance_objective(const vector<Individual> &res, const int obj);
    /**
     *
     * @param res
     * @return Map of crowding distance and individuals
     */
    map<double, vector<Individual>> compute_crowding_distance(const vector<Individual> &res);

    virtual //size_to_select is always smaller than res
    vector<Individual> select_best_crowding_distance(const vector<Individual> &res, int size_to_select);

    int run();
};


#endif //C___NSGA_NSGA_H
