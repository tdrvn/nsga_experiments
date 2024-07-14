#ifndef C___NSGA_NSGA_H
#define C___NSGA_NSGA_H

#include "Benchmark.h"
#include "Individual.h"
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <limits>
#include <map>
#include <chrono>

using namespace std;

template <std::size_t N_OBJ>
class NSGA {
public:
    Benchmark<N_OBJ> &f;
    int b_type = 0;
    vector<Individual> pop;
    int POP_SIZE;

    double total_time_non_dominated_sorting = 0;
    double total_time_crowding_distance_computation = 0;
    double total_time_tie_breaking = 0;

    NSGA(int n, int population_size, Benchmark<N_OBJ> &bench): POP_SIZE(population_size), f(bench){
        for(int i = 0; i< POP_SIZE; i++){
            Individual x(n);
            x.initialize_individual();
            pop.push_back(x);
        }
    }

    /**
     * @return For each rank-value the individuals with that rank.
     */
    map<int, vector<Individual> > non_dominated_sort(vector<Individual> &res);

    /**
     *
     * @param res
     * @return Computes in the same order.
     */
    vector<double> compute_crowding_distance_objective(const vector<std::array<int, N_OBJ>> &values, const int obj);
    /**
     *
     * @param res
     * @return Map of crowding distance and individuals
     */
    map<double, vector<Individual>> compute_crowding_distance(vector<Individual> &res);

    virtual //size_to_select is always smaller than res
    vector<Individual> select_best_crowding_distance(vector<Individual> &res, int size_to_select);

    long long run();
};


#endif //C___NSGA_NSGA_H
