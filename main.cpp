#include <iostream>
#include <fstream>
#include "NSGA.h"
#include "NSGA.cpp"
#include "Balanced_NSGA.h"
#include "Balanced_NSGA.cpp"
#include "OneMinMaxBenchmark.cpp"
#include "OneJumpZeroJumpBenchmark.cpp"
#include "LeadingOnesTrailingZeroBenchmark.cpp"
#include "mOneMinMaxBenchmark.cpp"
#include "globals.h"
#include <stdio.h>



int main() {
    std::ofstream fout("experiment-2oneminmax.csv");
   // fout << "\nBenchmark,n,k,Pop_size,Number_run,Seed,Runtime_Pareto_front,Variant_NSGA\n";
    long long seed = 4624637685;
    const int RUNS = 5;
    const int NMIN = 40;
    const int NMAX = 150;
    {
//        for(int k = 2; k <= 3; k++){
//            for (int n = NMIN; n <= NMAX; n += 10) {
//                for (int coef = 2; coef <= 8; coef *= 2) {
//                    if(pow(n, k + 2) <= 1e8){
//                        for (int nr_run = 1; nr_run <= RUNS; nr_run++) {
//                            auto curr_seed = (seed << 15) + (seed * n * coef * nr_run) ^ seed;
//                            seed = curr_seed;
//                            rand_gen.seed(seed);
//                            rand_gen.discard(1000000);
//
//                            OneJumpZeroJumpBenchmark f(n, k);
//                            int pop_size = coef * f.PARETO_FRONT_SIZE;
//                            NSGA<2> standard_nsga(n, pop_size, f);
//                            standard_nsga.run();
//                            auto rt = f.fitness_function_calls;
//                            fout << "OneJumpZeroJumpBenchmark," << n << "," << k << "," << pop_size << "," << nr_run << "," << curr_seed
//                                 << "," << rt << "," << "standard" << std::endl;
//                        }
//                    }
//                }
//            }
//        }
        for(int k = 1; k <=1; k++) {
            for (int n = NMIN; n <= NMAX; n += 20) {
                for (int coef = 1; coef <= 4; coef *= 2) {
                    for (int nr_run = 1; nr_run <= RUNS; nr_run++) {
                            auto curr_seed = (seed << 15) + (seed * n * coef * nr_run) ^ seed;
                            seed = curr_seed;
                            std::cerr<<curr_seed<<" ";
                            rand_gen.seed(seed);
                            rand_gen.discard(1000000);

                            MOneMinMaxBenchmark<4> f(n);

                            int pop_size = f.PARETO_FRONT_SIZE + coef * 4 * (n/2 + 1);
                            Balanced_NSGA<4> balanced_nsga(n, pop_size, f);
                            balanced_nsga.b_type = 1;
                            balanced_nsga.run();
                            auto rt = f.fitness_function_calls;
                            fout << "2OneMinMax," << n << "," << k << "," << pop_size << "," << nr_run
                                 << ","
                                 << seed
                                 << "," << rt << "," << "balanced" << std::endl;

                    }
                }
            }
        }
    }
}
