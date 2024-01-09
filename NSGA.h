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
    map<int, vector<Individual> > non_dominated_sort(const vector<Individual> &res){
        vector<pair<int, int>> values (res.size());
        for(int i = 0; i < res.size(); i++){
            values[i] = f.compute(res[i]);
        }
        vector<int> number_dominated (values.size());
        vector<vector<int>> positions_dominating(values.size());
        for(int i = 0; i < values.size(); i++){
            for(int j = 0; j < values.size(); j++){
                if(values[j].first >= values[i].first && values[j].second >= values[i].second &&
                    values[j].first + values[j].second > values[i].first + values[i].second){

                    number_dominated[i]++;
                    positions_dominating[j].push_back(i);
                }

            }
        }

        map<int, vector<Individual> > ans;
        int rank = 0;
        while(true){
            vector<Individual> current_rank;
            vector<int> current_rank_idx;
            for(int i = 0; i < number_dominated.size(); i++){
                if(number_dominated[i] == 0){
                    current_rank.push_back(res[i]);
                    current_rank_idx.push_back(i);
                }
            }
            if(current_rank.empty())
                break;
            ans[rank] = current_rank;
            rank++;
            for(auto i: current_rank_idx){
                number_dominated[i] = -1;
                for(auto dom:positions_dominating[i]){
                    number_dominated[dom]--;
                }
            }
        }
        return ans;
    }

    /**
     *
     * @param res
     * @return Computes in the same order.
     */
    vector<double> compute_crowding_distance_objective(const vector<Individual> &res, const int obj){
        vector<pair<int, int>> val_ind(res.size());

        for(int i = 0; i < res.size(); i++){
            auto value = f.compute(res[i]);
            if(obj == 0)
                val_ind[i] = {value.first, i};
            else
                val_ind[i] = {value.second, i};
        }
        sort(val_ind.begin(), val_ind.end());

        vector<double> ans(val_ind.size(), 0);
        if(val_ind.empty())
            return ans;
        ans[val_ind.front().second] = numeric_limits<double>::infinity();
        ans[val_ind.back().second] = numeric_limits<double>::infinity();
        int minn = val_ind.front().first, maxx = val_ind.back().first;
        for(int i = 1; i < val_ind.size() - 1; i++){
            double score = 0;
            if(maxx != minn)
                score = (double)(val_ind[i + 1].first - val_ind[i - 1].first) / (maxx - minn);
            ans[val_ind[i].second] = score;
        }
        return ans;
    }
    /**
     *
     * @param res
     * @return Map of crowding distance and individuals
     */
    map<double, vector<Individual>> compute_crowding_distance(const vector<Individual> &res){
        auto a1 = compute_crowding_distance_objective(res, 0);
        auto a2 = compute_crowding_distance_objective(res, 1);

        map<double, vector<Individual>> ans;
        for(int i = 0; i < res.size(); i++){
            double cd = a1[i] + a2[i];
            if(ans.count(cd)){
                ans[cd].push_back(res[i]);
            }
            else{
                ans[cd] = {res[i]};
            }
        }
        return ans;
    }

    virtual //size_to_select is always smaller than res
    vector<Individual> select_best_crowding_distance(const vector<Individual> &res, int size_to_select){
        vector<Individual> selection;
        if(size_to_select == 0)
            return selection;

        auto cd_sorted = compute_crowding_distance(res);
        for(auto itr = cd_sorted.rbegin(); itr != cd_sorted.rend() && selection.size() < size_to_select; itr++){
          auto &elements = (*itr).second;
          std::shuffle(elements.begin(), elements.end(), rand_gen);

          while(elements.size() > 0 && selection.size() < size_to_select){
              selection.push_back(elements.back());
              elements.pop_back();
          }
        }
        return selection;
    }

    int run(){
        int iterations = 0;
        while(f.is_pareto_front_complete(pop) == false){
            vector<Individual> offspring = pop;
            for(auto &x:offspring)
                x.mutate();

            auto total_pop = pop + offspring;

            auto ranks = non_dominated_sort(total_pop);
            vector<Individual> new_pop;

            for(auto &kv_pair:ranks){
                if(new_pop.size() == POP_SIZE)
                    break;
                if(new_pop.size() + kv_pair.second.size() <= POP_SIZE){
                    new_pop += kv_pair.second;
                }
                else{
                    auto selected = select_best_crowding_distance(kv_pair.second, POP_SIZE - new_pop.size());
                    new_pop += selected;
                }
            }

            pop = new_pop;
            iterations ++;
        }
        return iterations;
    }
};


#endif //C___NSGA_NSGA_H
