//
// Created by tudor on 07/01/24.
//

#ifndef C___NSGA_ONEMINMAXBENCHMARK_CPP
#define C___NSGA_ONEMINMAXBENCHMARK_CPP

#include "Benchmark.h"
#include <set>
#include <iostream>

class OneMinMaxBenchmark : public Benchmark{
public:
    int PARETO_FRONT_SIZE = n + 1;

    OneMinMaxBenchmark(int _n) : Benchmark(_n) {}

    virtual std::pair<int, int> compute(const Individual &x){
        fitness_function_calls ++;
        std::pair<int, int> ans = {0, 0};
        for(int i = 0; i < n; i++){
            if(x.bits[i] == 0)
                ans.first++;
            else
                ans.second++;
        }
        return ans;
    }


    virtual bool is_pareto_front_complete(std::vector<Individual> &pop){
        std::set<std::pair<int, int>> values;
        for(int i = 0; i < pop.size(); i++){
            values.insert(compute(pop[i]));
        }
        std::cerr<<"Pareto front is: "<<values.size()<<" out of "<<PARETO_FRONT_SIZE<<std::endl;
        if(values.size() == PARETO_FRONT_SIZE)
            return true;
        return false;
    }

};

#endif
