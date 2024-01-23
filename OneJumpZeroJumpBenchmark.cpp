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

    virtual std::array<int, 2> compute(const Individual &x){
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


    virtual bool is_pareto_front_complete(const std::vector<Individual> &pop){
        std::map<std::array<int, 2>, int> values;
        for(int i = 0; i < pop.size(); i++){
            auto val = compute(pop[i]);
            if(val[0] + val[1] == n + 2 * k)
                values[val] = values[val] + 1;

        }
//        bool inner = true;
//        for(int i = k; i <= n - k; i++){
//            if(values.count({k + i, k +  n - i}) == false)
//                inner = false;
//        }
//        if(inner && first_time_inner == -1){
//            first_time_inner = fitness_function_calls;
//            std::cerr<<"Reached inner PF after "<<first_time_inner<<" calls"<<std::endl;
//        }
//        if(first_time_inner != -1){
//            std::cerr<<"left pop: "<<values[{2*k, n}]<<"\n";
//            std::cerr<<"right pop: "<<values[{n, 2*k}]<<"\n";
//        }
//        std::cerr<<"Pareto front is: "<<values.size()<<" out of "<<PARETO_FRONT_SIZE<<std::endl;
//        std::cerr<<"The values are:";
//        for(auto val: values){
//            std::cerr<<"( "<<val.first<<" "<<val.second<<" ), ";
//        }
       // std::cerr<<"\n";
        if(values.size() == PARETO_FRONT_SIZE)
            return true;
        return false;
    }



};

#endif
