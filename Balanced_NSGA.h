//
// Created by tudor on 07/01/24.
//

#ifndef C___NSGA_BALANCED_NSGA_H
#define C___NSGA_BALANCED_NSGA_H

#include "NSGA.h"
using namespace std;
template <std::size_t N_OBJ>
class Balanced_NSGA: public NSGA<N_OBJ>{
public:

    Balanced_NSGA(int _n, int population_size, Benchmark<N_OBJ> &bench): NSGA<N_OBJ>(_n, population_size, bench) {}

    vector<std::shared_ptr<Individual>> select_best_crowding_distance(const vector<std::shared_ptr<Individual>> &res, int size_to_select) override;
};


#endif //C___NSGA_BALANCED_NSGA_H
