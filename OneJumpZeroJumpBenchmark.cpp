//
// Created by tudor on 07/01/24.
//

#ifndef C___NSGA_ONEJUMPZEROJUMP_CPP
#define C___NSGA_ONEJUMPZEROJUMP_CPP

#include "Benchmark.h"
#include <map>
#include <iostream>

class OneJumpZeroJumpBenchmark : public Benchmark<2>{
public:
    int PARETO_FRONT_SIZE;


    OneJumpZeroJumpBenchmark(int _n, int _k) : Benchmark(_n), PARETO_FRONT_SIZE(_n - 2*_k + 3) { k = _k; }


    bool is_pareto_front_complete(const std::vector<std::shared_ptr<Individual>> &pop) override{
        std::map<std::array<int, 2>, int> values;
        for(int i = 0; i < pop.size(); i++){
            auto val = getCompute(pop[i]);
            if(val[0] + val[1] == n + 2 * k)
                values[val] = values[val] + 1;
        }
        if(values.size() == PARETO_FRONT_SIZE)
            return true;
        return false;
    }

private:
    std::array<int, 2> compute(const Individual &x) override{
        //this->fitness_function_calls ++;
        int nr0 = 0, nr1 = 0;
        for(int i = 0; i < n; i++){
            if(x.bits[i] == 0)
                nr0++;
            else
                nr1++;
        }
        std::array<int, 2> ans = {0, 0};
        if(nr1 <= n - k || nr1 == n)
            ans[0] = k + nr1;
        else
            ans[0] = n - nr1;

        if(nr0 <= n - k || nr0 == n)
            ans[1] = k + nr0;
        else
            ans[1] = n - nr0;

        return ans;
    }


};

#endif
