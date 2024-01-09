//
// Created by tudor on 07/01/24.
//

#ifndef C___NSGA_ONEJUMPZEROJUMP_CPP
#define C___NSGA_ONEJUMPZEROJUMP_CPP

#include "Benchmark.h"
#include <set>
#include <iostream>

class OneJumpZeroJumpBenchmark : public Benchmark{
public:
    int k;
    int PARETO_FRONT_SIZE;

    OneJumpZeroJumpBenchmark(int _n, int _k) : Benchmark(_n), k(_k), PARETO_FRONT_SIZE(_n - 2*_k + 3) {}

    virtual std::pair<int, int> compute(const Individual &x){
        this->fitness_function_calls ++;
        int nr0 = 0, nr1 = 0;
        for(int i = 0; i < n; i++){
            if(x.bits[i] == 0)
                nr0++;
            else
                nr1++;
        }
        std::pair<int, int> ans = {0, 0};
        if(nr1 <= n - k || nr1 == n)
            ans.first = k + nr1;
        else
            ans.first = n - nr1;

        if(nr0 <= n - k || nr0 == n)
            ans.second = k + nr0;
        else
            ans.second = n - nr0;

        return ans;
    }


    virtual bool is_pareto_front_complete(std::vector<Individual> &pop){
        std::set<std::pair<int, int>> values;
        for(int i = 0; i < pop.size(); i++){
            values.insert(compute(pop[i]));
        }
        std::cerr<<"Pareto front is: "<<values.size()<<" out of "<<PARETO_FRONT_SIZE<<std::endl;
        std::cerr<<"The values are:";
        for(auto val: values){
            std::cerr<<"( "<<val.first<<" "<<val.second<<" ), ";
        }
        std::cerr<<"\n";
        if(values.size() == PARETO_FRONT_SIZE)
            return true;
        return false;
    }

};

#endif
