//
// Created by tudor on 07/01/24.
//

#ifndef C___NSGA_INDIVIDUAL_H
#define C___NSGA_INDIVIDUAL_H

#include<bitset>
#include "globals.h"
#include<vector>

class Individual {
public:
    std::vector<bool> bits;
    int n;
    explicit Individual(int _n) : n(_n), bits(std::vector<bool> (_n, 0)) {
        initialize_individual();
    }

    void initialize_individual(){
        std::bernoulli_distribution bit_distrib((double)1.0/2);
        for(int i = 0; i < n; i++){
            bits[i] = bit_distrib(rand_gen);
        }
    }

    void mutate(){
        std::bernoulli_distribution modify_bit((double)1.0/n);
        for(int i = 0; i < n; i++){
            bits[i] = bits[i] ^ modify_bit(rand_gen);
        }
    }




};


#endif //C___NSGA_INDIVIDUAL_H
