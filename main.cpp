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


void test_OneMinMax_classic(int k, int n, int coef, unsigned long seed, int nr_run, std::ostream& fout){
    rand_gen.seed(seed);

    OneMinMaxBenchmark f(n);
    int pop_size = coef * f.PARETO_FRONT_SIZE;

    NSGA<2> standard_nsga(n, pop_size, f);
    standard_nsga.run();
    auto rt = f.fitness_function_calls;
    fout << "OneMinMax," << n << "," << k << "," << pop_size << "," << nr_run << "," << seed
         << "," << rt << "," << "classic" << std::endl;
}
void test_OneMinMax_balanced(int k, int n, int coef, unsigned long seed, int nr_run, std::ostream& fout){
    rand_gen.seed(seed);

    OneMinMaxBenchmark f(n);
    int pop_size = coef * f.PARETO_FRONT_SIZE;

    Balanced_NSGA<2> balanced_nsga(n, pop_size, f);
    balanced_nsga.run();
    auto rt = f.fitness_function_calls;
    fout << "OneMinMax," << n << "," << k << "," << pop_size << "," << nr_run << "," << seed
         << "," << rt << "," << "balanced" << std::endl;
}

void test_LeadingOnesTrailingZeros_classic(int k, int n, int coef, unsigned long seed, int nr_run, std::ostream& fout){
    rand_gen.seed(seed);

    LeadingOnesTrailingZeroBenchmark f(n);
    int pop_size = coef * f.PARETO_FRONT_SIZE;

    NSGA<2> standard_nsga(n, pop_size, f);
    standard_nsga.run();
    auto rt = f.fitness_function_calls;
    fout << "LeadingOnesTrailingZeros," << n << "," << k << "," << pop_size << "," << nr_run << "," << seed
         << "," << rt << "," << "classic" << std::endl;
}
void test_LeadingOnesTrailingZeros_balanced(int k, int n, int coef, unsigned long seed, int nr_run, std::ostream& fout){
    rand_gen.seed(seed);

    LeadingOnesTrailingZeroBenchmark f(n);
    int pop_size = coef * f.PARETO_FRONT_SIZE;

    Balanced_NSGA<2> balanced_nsga(n, pop_size, f);
    balanced_nsga.run();
    auto rt = f.fitness_function_calls;
    fout << "LeadingOnesTrailingZeros," << n << "," << k << "," << pop_size << "," << nr_run << "," << seed
         << "," << rt << "," << "balanced" << std::endl;
}

void test_OneJumpZeroJump_classic(int k, int n, int coef, unsigned long seed, int nr_run, std::ostream& fout){
    rand_gen.seed(seed);

    OneJumpZeroJumpBenchmark f(n, k);
    int pop_size = coef * f.PARETO_FRONT_SIZE;

    NSGA<2> standard_nsga(n, pop_size, f);
    standard_nsga.b_type = 3; // in order to optimize rank sorting
    standard_nsga.run();
    auto rt = f.fitness_function_calls;
    fout << "OneJumpZeroJump," << n << "," << k << "," << pop_size << "," << nr_run << "," << seed
         << "," << rt << "," << "classic" << std::endl;
}
void test_OneJumpZeroJump_balanced(int k, int n, int coef, unsigned long seed, int nr_run, std::ostream& fout){
    rand_gen.seed(seed);

    OneJumpZeroJumpBenchmark f(n, k);
    int pop_size = coef * f.PARETO_FRONT_SIZE;

    Balanced_NSGA<2> balanced_nsga(n, pop_size, f);
    balanced_nsga.b_type = 3; // in order to optimize rank sorting
    balanced_nsga.run();
    auto rt = f.fitness_function_calls;
    fout << "OneJumpZeroJump," << n << "," << k << "," << pop_size << "," << nr_run << "," << seed
         << "," << rt << "," << "balanced" << std::endl;
}

int main() {
    std::ofstream fout("experiments-final-lotz-extra.csv");
    //fout << "Benchmark,n,k,Pop_size,Number_run,Seed,Runtime_Pareto_front,Variant_NSGA\n";
    std::mt19937 seed_generator(1);
    const int RUNS = 20;
    const int EXTRA_RUNS = 30;

    const int NMIN = 30;
    const int NMAX = 120;


    //OneMinMax
    {
        /**
         * Note that for OneMinMax there are 3 different seeds set, as we needed to add extra tests without invalidating the old ones.
         * For the other benchmarks, there is just one run with all the tests at the same time.
         * OneJumpZeroJump was too slow to run for all the values and was ended sooner
         */
        /*
       seed_generator.seed(1);
       for(int k = 1; k <= 1; k++){
           for (int n = NMIN; n <= NMAX; n += 10) {
               for (int coef = 2; coef <= 8; coef *= 2) {
                   for (int nr_run = 1; nr_run <= RUNS; nr_run++) {
                       //classic
                       {
                           auto seed = seed_generator();

                           test_OneMinMax_classic(k, n, coef, seed, nr_run, fout);
                       }
                       //balanced
                       {
                           auto seed = seed_generator();

                           test_OneMinMax_balanced(k, n, coef, seed, nr_run, fout);
                       }
                   }
               }
           }
       }

       //TRY for N = 16 M
       seed_generator.seed(2);
      // one min max for N = 16M,  just 30 runs
       for(int k = 1; k <= 1; k++){
           for (int n = NMIN; n <= NMAX; n += 10) {
               for (int coef = 16; coef <= 16; coef *= 2) {
                   for (int nr_run = 1; nr_run <= RUNS; nr_run++) {
                       //classic
                       {
                           auto seed = seed_generator();

                           test_OneMinMax_classic(k, n, coef, seed, nr_run, fout);
                       }
                       //balanced
                       {
                           auto seed = seed_generator();

                           test_OneMinMax_balanced(k, n, coef, seed, nr_run, fout);
                       }
                   }
               }
           }
       }
       //EXTRA RUNS OMM
       seed_generator.seed(3);
       //OneMinMax
       for(int k = 1; k <= 1; k++){
           for (int n = NMIN; n <= NMAX; n += 10) {
               for (int coef = 2; coef <= 16; coef *= 2) {
                   for (int nr_run = RUNS + 1; nr_run <= RUNS + EXTRA_RUNS; nr_run++) {
                       //classic
                       {
                           auto seed = seed_generator();

                           test_OneMinMax_classic(k, n, coef, seed, nr_run, fout);
                       }
                       //balanced
                       {
                           auto seed = seed_generator();

                           test_OneMinMax_balanced(k, n, coef, seed, nr_run, fout);
                       }
                   }
               }
           }
       }
       */
    }


    //LeadingOnesTrailingZeros
    {
        seed_generator.seed(4);
        for (int k = 1; k <= 1; k++) {
            for (int n = NMIN; n <= NMAX; n += 10) {
                for (int coef = 2; coef <= 16; coef *= 2) {
                    for (int nr_run = 1; nr_run <= RUNS + EXTRA_RUNS; nr_run++) {
                        //classic
                        {
                            auto seed = seed_generator();

                            test_LeadingOnesTrailingZeros_classic(k, n, coef, seed, nr_run, fout);
                        }
                        //balanced
                        {
                            auto seed = seed_generator();

                            test_LeadingOnesTrailingZeros_balanced(k, n, coef, seed, nr_run, fout);
                        }
                    }
                }
            }
        }
    }

    //OneJumpZeroJump
    {
        /*
        seed_generator.seed(5);
        for (int k = 3; k <= 3; k++) {
            for (int n = NMIN; n <= NMAX; n += 10) {
                for (int coef = 2; coef <= 8; coef *= 2) {
                    for (int nr_run = 1; nr_run <= RUNS; nr_run++) {
                        //classic
                        {
                            auto seed = seed_generator();

                            test_OneJumpZeroJump_classic(k, n, coef, seed, nr_run, fout);
                        }
                        //balanced
                        {
                            auto seed = seed_generator();

                            test_OneJumpZeroJump_balanced(k, n, coef, seed, nr_run, fout);
                        }
                    }
                }
            }
        }
    }
    */
    }
}