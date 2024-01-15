#include "NSGA.h"

template <std::size_t N_OBJ>
map<int, vector<Individual> > NSGA<N_OBJ>::non_dominated_sort(vector<Individual> &res){

//    //special case to not do this in the case of OneMinMax
//    if(b_type == 1){
//        map<int, vector<Individual> > ans;
//        ans[0] = std::move(res);
//        res.clear();
//        return ans;
//    }

//instead of O(Pop_size ^ 2), we do O(f(Pop_size)^2) which should be faster for our benchmarks
    map<std::array<int, N_OBJ>, int> ranks_for_values;
    for(int i = 0; i < res.size(); i++){
        auto val = f.compute(res[i]);
        ranks_for_values[val] = 0;
    }
    for(auto itr = ranks_for_values.rbegin(); itr != ranks_for_values.rend(); itr++){
        int mxpref = 0;
        auto &b1 = (*itr).first;
        for(auto itr2 = ranks_for_values.rbegin(); itr2 != itr; itr2++){
            if((*itr2).second <= mxpref)
                continue;
            auto &b2 = (*itr2).first; // i check if b2 dominates b1
            bool eq_dominates= true;
            bool strictly_dominates = false;

            for(int l = 0; l < N_OBJ; l++){
                if(b2[l] < b1[l])
                    eq_dominates = false;
                if(b2[l] > b1[l])
                    strictly_dominates = true;
            }

            if(eq_dominates && strictly_dominates){
                mxpref = (*itr2).second;
            }
        }
        (*itr).second = mxpref + 1;
    }

    map<int, vector<Individual>> ans;
    for(int i = 0; i < res.size();i++){

        int rank = ranks_for_values[f.compute(res[i])];
        if(ans.count(rank))
            ans[rank].push_back(std::move(res[i]));
        else
            ans[rank] = {std::move(res[i])};
    }

//
//    vector<int> number_dominated (values.size());
//    unordered_map<int, vector<int>> positions_dominating; // probably huge
//    for(int i = 0; i < values.size(); i++){
//        for(int j = 0; j < values.size(); j++){
//
//
//        }
//    }
//
//    map<int, vector<Individual> > ans;
//    int rank = 0;
//    while(true){
//        vector<Individual> current_rank;
//        vector<int> current_rank_idx;
//        for(int i = 0; i < number_dominated.size(); i++){
//            if(number_dominated[i] == 0){
//                current_rank.push_back(std::move(res[i]));
//                current_rank_idx.push_back(i);
//            }
//        }
//        if(current_rank.empty())
//            break;
//        ans[rank] = std::move(current_rank);
//        rank++;
//        for(auto i: current_rank_idx){
//            number_dominated[i] = -1;
//            for(auto dom:positions_dominating[i]){
//                number_dominated[dom]--;
//            }
//        }
//    }
    res.clear();
    return ans;
}

template <std::size_t N_OBJ>
vector<double> NSGA<N_OBJ>::compute_crowding_distance_objective(const vector<std::array<int, N_OBJ>> &values, const int obj){
    vector<pair<int, int>> val_ind(values.size());

    for(int i = 0; i < values.size(); i++){
        val_ind[i] = {values[i][obj], i};
    }
    //sort just by cd
    sort(val_ind.begin(), val_ind.end(),
         [](const std::pair<int,int>& p1, const std::pair<int,int>& p2)
            { return p1.first < p2.first; });

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

template <std::size_t N_OBJ>
map<double, vector<Individual>> NSGA<N_OBJ>::compute_crowding_distance(vector<Individual> &res){ // destroys res
    vector<std::array<int, N_OBJ>> values;
    for(auto x:res){
        values.push_back(f.compute(x));
    }

    vector<double> cd_score(res.size(), 0);
    for(int l=0; l < N_OBJ; l++){
        auto a (std::move(compute_crowding_distance_objective(values, l)));
        for(int i = 0; i < a.size(); i++)
            cd_score[i] += a[i];
    }

    map<double, vector<Individual>> ans;
    for(int i = 0; i < res.size(); i++){
        auto cd = cd_score[i];
        if(ans.count(cd)){
            ans[cd].push_back(std::move(res[i]));
        }
        else{
            ans[cd] = {std::move(res[i])};
        }
    }
    res.clear();
    return ans;
}

template <std::size_t N_OBJ>
vector<Individual> NSGA<N_OBJ>::select_best_crowding_distance(vector<Individual> &res, int size_to_select){ // destroys res
    vector<Individual> selection;
    if(size_to_select == 0)
        return selection;

    auto cd_sorted = this->compute_crowding_distance(res); // destroys res
    for(auto itr = cd_sorted.rbegin(); itr != cd_sorted.rend() && selection.size() < size_to_select; itr++){
        auto &elements = (*itr).second;
        std::shuffle(elements.begin(), elements.end(), rand_gen);
        if(selection.size() + elements.size() <= size_to_select){
            std::move(elements.begin(), elements.end(), std::back_inserter(selection));
            elements.clear();
        }
        else{
            //only add extra elements
            while(elements.size() > 0 && selection.size() < size_to_select){
                selection.push_back(std::move(elements.back()));
                elements.pop_back();
            }
        }
    }
    return selection;
}

template <std::size_t N_OBJ>
long long NSGA<N_OBJ>::run(){
    int iterations = 0;
    while(f.is_pareto_front_complete(pop) == false){
        f.fitness_function_calls += (long long)POP_SIZE;

        vector<Individual> offspring = pop;
        for(auto &x:offspring)
            x.mutate();


        auto &total_pop = pop;
        std::move(offspring.begin(), offspring.end(), std::back_inserter(total_pop));


        auto ranks (std::move(non_dominated_sort(total_pop)));
        vector<Individual> new_pop;

        for(auto &kv_pair:ranks){
            if(new_pop.size() == POP_SIZE)
                break;
            if(new_pop.size() + kv_pair.second.size() <= POP_SIZE){
                std::move(kv_pair.second.begin(), kv_pair.second.end(), std::back_inserter(new_pop));
            }
            else{
                auto selected(std::move(select_best_crowding_distance(kv_pair.second, POP_SIZE - new_pop.size())));
                std::move(selected.begin(), selected.end(), std::back_inserter(new_pop));
            }
        }

        pop = std::move(new_pop);
        iterations ++;
    }
    return iterations;
}