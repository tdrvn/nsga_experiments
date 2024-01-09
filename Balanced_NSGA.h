//
// Created by tudor on 07/01/24.
//

#ifndef C___NSGA_BALANCED_NSGA_H
#define C___NSGA_BALANCED_NSGA_H

#include "NSGA.h"
using namespace std;
class Balanced_NSGA: public NSGA{
public:

    Balanced_NSGA(int _n, int population_size, Benchmark &bench): NSGA(_n, population_size, bench) {}

    vector<Individual> select_best_crowding_distance(const vector<Individual> &res, int size_to_select);
};


#endif //C___NSGA_BALANCED_NSGA_H
