#include "Balanced_NSGA.h"

vector<Individual> Balanced_NSGA::select_best_crowding_distance(const vector<Individual> &res, int size_to_select){
    //std::cerr<<"Using the right one!"<<std::endl;
    vector<Individual> selection;
    if(size_to_select == 0)
        return selection;

    auto cd_sorted = this->compute_crowding_distance(res);
    for(auto itr = cd_sorted.rbegin(); itr != cd_sorted.rend() && selection.size() < size_to_select; itr++){
        auto &elements = (*itr).second;
        std::shuffle(elements.begin(), elements.end(), rand_gen);

        if(selection.size() + elements.size() <= size_to_select){
            selection += elements;
        }
        else{
            int remaining_to_select = size_to_select - selection.size();
            map<pair<int, int>, vector<Individual> > value_map;
            for(auto x:elements){
                auto val = this->f.compute(x);
                if(value_map.count(val))
                    value_map[val].push_back(x);
                else
                    value_map[val] = {x};
            }

            int number_values = value_map.size();
            vector<Individual> remaining;
            for(auto &kv: value_map){
                for(int i = 0; kv.second.empty() == false && i <= remaining_to_select/number_values ; i++){
                    selection.push_back(kv.second.back());
                    kv.second.pop_back();
                }
                remaining += kv.second;
            }

            std::shuffle(remaining.begin(), remaining.end(), rand_gen);
            while(selection.size() < size_to_select){
                selection.push_back(remaining.back());
                remaining.pop_back();
            }
        }
    }
    return selection;
}