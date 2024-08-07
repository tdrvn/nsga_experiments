#ifndef C___NSGA_LEADINGONESTRAILINGZEROBENCHMARK_H
#define C___NSGA_LEADINGONESTRAILINGZEROBENCHMARK_H

#include "Benchmark.h"
#include <iostream>
#include <set>

class LeadingOnesTrailingZeroBenchmark : public Benchmark<2>{
public:
    int PARETO_FRONT_SIZE = n + 1;

    LeadingOnesTrailingZeroBenchmark(int _n) : Benchmark(_n) {}

    bool is_pareto_front_complete(const std::vector<std::shared_ptr<Individual>> &pop) override{
        std::set<std::array<int, 2>> values;
        for(int i = 0; i < pop.size(); i++){
            auto x = getCompute(pop[i]);
            if(x[0] + x[1] == n)
                values.insert(x);
        }
        //std::cerr<<"Pareto front is: "<<values.size()<<" out of "<<PARETO_FRONT_SIZE<<std::endl;
        if(values.size() == PARETO_FRONT_SIZE)
            return true;
        return false;
    }

private:
    std::array<int, 2> compute(const Individual &x) override{
        //fitness_function_calls ++;
        std::array<int, 2> ans = {0, 0};
        for(int i = 0; i < n; i++){
            if(x.bits[i] == 1)
                ans[0]++;
            else
                break;
        }

        for(int i = n - 1; i >= 0; i--){
            if(x.bits[i] == 0)
                ans[1]++;
            else
                break;
        }
        return ans;
    }
};


#endif //C___NSGA_LEADINGONESTRAILINGZEROBENCHMARK_H
