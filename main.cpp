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
    std::ofstream fout("experiments-final.csv");
    fout << "Benchmark,n,k,Pop_size,Number_run,Seed,Runtime_Pareto_front,Variant_NSGA\n";
    std::mt19937 seed_generator(1);
    const int RUNS = 20;
    const int NMIN = 30;
    const int NMAX = 120;

    //OneMinMax
    for(int k = 1; k <= 1; k++){
        for (int n = NMIN; n <= NMAX; n += 10) {
            for (int coef = 2; coef <= 8; coef *= 2) {
                for (int nr_run = 1; nr_run <= RUNS; nr_run++) {
                    //classic
                    {
                        auto seed = seed_generator();
                        rand_gen.seed(seed);

                        OneMinMaxBenchmark f(n);
                        int pop_size = coef * f.PARETO_FRONT_SIZE;
                        NSGA<2> standard_nsga(n, pop_size, f);
                        standard_nsga.run();
                        auto rt = f.fitness_function_calls;
                        fout << "OneMinMax," << n << "," << k << "," << pop_size << "," << nr_run << "," << seed
                             << "," << rt << "," << "classic" << std::endl;
                    }
                    //balanced
                    {
                        auto seed = seed_generator();
                        rand_gen.seed(seed);

                        OneMinMaxBenchmark f(n);
                        int pop_size = coef * f.PARETO_FRONT_SIZE;
                        Balanced_NSGA<2> balanced_nsga(n, pop_size, f);
                        balanced_nsga.run();
                        auto rt = f.fitness_function_calls;
                        fout << "OneMinMax," << n << "," << k << "," << pop_size << "," << nr_run << "," << seed
                             << "," << rt << "," << "balanced" << std::endl;
                    }
                }
            }
        }
    }

    //LeadingOnesTrailingZeros
    for(int k = 1; k <= 1; k++){
        for (int n = NMIN; n <= NMAX; n += 10) {
            for (int coef = 2; coef <= 8; coef *= 2) {
                for (int nr_run = 1; nr_run <= RUNS; nr_run++) {
                    //classic
                    {
                        auto seed = seed_generator();
                        rand_gen.seed(seed);

                        LeadingOnesTrailingZeroBenchmark f(n);
                        int pop_size = coef * f.PARETO_FRONT_SIZE;
                        NSGA<2> standard_nsga(n, pop_size, f);
                        standard_nsga.run();
                        auto rt = f.fitness_function_calls;
                        fout << "LeadingOnesTrailingZeros," << n << "," << k << "," << pop_size << "," << nr_run << "," << seed
                             << "," << rt << "," << "classic" << std::endl;
                    }
                    //balanced
                    {
                        auto seed = seed_generator();
                        rand_gen.seed(seed);

                        LeadingOnesTrailingZeroBenchmark f(n);
                        int pop_size = coef * f.PARETO_FRONT_SIZE;
                        Balanced_NSGA<2> balanced_nsga(n, pop_size, f);
                        balanced_nsga.run();
                        auto rt = f.fitness_function_calls;
                        fout << "LeadingOnesTrailingZeros," << n << "," << k << "," << pop_size << "," << nr_run << "," << seed
                             << "," << rt << "," << "balanced" << std::endl;
                    }
                }
            }
        }
    }

    //OneJumpZeroJump
    for(int k = 3; k <= 3; k++){
        for (int n = NMIN; n <= NMAX; n += 10) {
            for (int coef = 2; coef <= 8; coef *= 2) {
                for (int nr_run = 1; nr_run <= RUNS; nr_run++) {
                    //classic
                    {
                        auto seed = seed_generator();
                        rand_gen.seed(seed);

                        OneJumpZeroJumpBenchmark f(n, k);
                        int pop_size = coef * f.PARETO_FRONT_SIZE;
                        NSGA<2> standard_nsga(n, pop_size, f);
                        standard_nsga.run();
                        auto rt = f.fitness_function_calls;
                        fout << "OneJumpZeroJump," << n << "," << k << "," << pop_size << "," << nr_run << "," << seed
                             << "," << rt << "," << "classic" << std::endl;
                    }
                    //balanced
                    {
                        auto seed = seed_generator();
                        rand_gen.seed(seed);

                        OneJumpZeroJumpBenchmark f(n, k);
                        int pop_size = coef * f.PARETO_FRONT_SIZE;
                        Balanced_NSGA<2> balanced_nsga(n, pop_size, f);
                        balanced_nsga.run();
                        auto rt = f.fitness_function_calls;
                        fout << "OneJumpZeroJump," << n << "," << k << "," << pop_size << "," << nr_run << "," << seed
                             << "," << rt << "," << "balanced" << std::endl;
                    }
                }
            }
        }
    }

}
