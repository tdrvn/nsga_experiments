#ifndef MONEMINMAXBENCHMARK_CPP
#define MONEMINMAXBENCHMARK_CPP

#include "Benchmark.h"
#include <map>
#include <iostream>
#include <cmath>

/**
 *
 * @tparam M has to be even, represents total number of functions
 *          M/2 has to divide n
 */
template <std::size_t M>
class MOneMinMaxBenchmark : public Benchmark<M>{
public:
    int PARETO_FRONT_SIZE = 0;
    int nprime = 0;
    explicit MOneMinMaxBenchmark(int _n) : Benchmark<M>(_n), PARETO_FRONT_SIZE(std::pow(this->n/2 + 1, M/2)), nprime(_n / (M/2)) {}

    virtual std::array<int, M> compute(const Individual &x){
        //fitness_function_calls ++;
        std::array<int, M> ans {};
        for(int l = 0; l < M/2; l++){
            for(int i = l * nprime; i < (l + 1)*nprime; i++){
                if(x.bits[i] == 0)
                    ans[2*l]++;
                else
                    ans[2*l + 1]++;
            }
        }
        return ans;
    }


    virtual bool is_pareto_front_complete(const std::vector<Individual> &pop){
        std::map<std::array<int, M>, int> values;
        for(int i = 0; i < pop.size(); i++){
            auto x = std::move(compute(pop[i]));
            values[x] = values[x] + 1;
        }
        std::cerr<<"Pareto front is: "<<values.size()<<" out of "<<PARETO_FRONT_SIZE<<std::endl;
        std::cerr<<"The values are:";
        for(auto val: values){
            std::cerr<<"( ";
            for(int i = 0; i < M; i++)
                std::cerr<<val.first[i]<<", ";
            std::cerr<<": "<<val.second<<" ";
            std::cerr<<" ), ";
        }
        std::cerr<<"\n";

        std::cerr<<"Pareto front is: "<<values.size()<<" out of "<<PARETO_FRONT_SIZE<<std::endl;
        if(values.size() == PARETO_FRONT_SIZE)
            return true;
        return false;
    }

};

#endif
