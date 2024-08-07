#include "Balanced_NSGA.h"
template <size_t N_OBJ>
vector<std::shared_ptr<Individual>> Balanced_NSGA<N_OBJ>::select_best_crowding_distance(const vector<std::shared_ptr<Individual>> &res, int size_to_select){
    //std::cerr<<"Using the right one!"<<std::endl;
    auto t_start = std::chrono::high_resolution_clock::now();

    vector<std::shared_ptr<Individual>> selection;
    if(size_to_select == 0) {
        auto t_end = std::chrono::high_resolution_clock::now();
        this->total_time_selection += std::chrono::duration_cast<std::chrono::duration<double>>(t_end - t_start).count();
        return selection;
    }

    auto cd_sorted = (this->compute_crowding_distance(res));
    for(auto itr = cd_sorted.rbegin(); itr != cd_sorted.rend() && selection.size() < size_to_select; itr++){
        auto& elements = (*itr).second;

        if(selection.size() + elements.size() <= size_to_select){
            std::move(elements.begin(), elements.end(), std::back_inserter(selection));
        }
        else{

            auto t_start1 = std::chrono::high_resolution_clock::now();
            int remaining_to_select = size_to_select - selection.size();

            unordered_map<std::array<int, N_OBJ>, vector<std::shared_ptr<Individual>>, typename Benchmark<N_OBJ>::HashFunction > value_map;
            for(auto& x:elements){
                auto val = this->f.getCompute(x);
                if(value_map.count(val))
                    value_map[val].emplace_back(x);
                else
                    value_map[val] = {x};
            }

            int number_values = value_map.size();
            vector<std::shared_ptr<Individual>> remaining{};
            for(auto &kv: value_map){
                for(int i = 0; !kv.second.empty() && i < remaining_to_select/number_values ; i++){
                    selection.emplace_back(std::move(kv.second.back()));
                    kv.second.pop_back();
                }
                std::move(kv.second.begin(), kv.second.end(), std::back_inserter(remaining));
            }

            if (selection.size() < size_to_select){
                auto csize = selection.size();
                std::sample(remaining.begin(), remaining.end(),std::back_inserter(selection), size_to_select - csize, rand_gen);
            }
            auto t_end1 = std::chrono::high_resolution_clock::now();
            this->total_time_tiebreaker += std::chrono::duration_cast<std::chrono::duration<double>>(t_end1 - t_start1).count();
        }
    }
    auto t_end = std::chrono::high_resolution_clock::now();
    this->total_time_selection += std::chrono::duration_cast<std::chrono::duration<double>>(t_end - t_start).count();
    return selection;
}