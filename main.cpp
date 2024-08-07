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
#include <chrono>

using namespace std::chrono;


void test_OneMinMax_classic(int k, int n, int coef, unsigned long seed, int nr_run, std::ostream &fout) {
    rand_gen.seed(seed);

    OneMinMaxBenchmark f(n);
    int pop_size = coef * f.PARETO_FRONT_SIZE;

    NSGA<2> standard_nsga(n, pop_size, f);
    auto start = high_resolution_clock::now();
    standard_nsga.run();
    auto end = high_resolution_clock::now();
    auto rt = f.fitness_function_calls;

    auto duration = duration_cast<std::chrono::duration<double>>(end - start).count();
    fout << "OneMinMax," << n << "," << k << "," << pop_size << "," << nr_run << "," << seed
         << "," << rt << "," << duration << "," << standard_nsga.total_time_non_dominated_sorting << ","
         << standard_nsga.total_time_crowding_distance_computation << "," << standard_nsga.total_time_selection << ", "
         << standard_nsga.total_time_tiebreaker << ", classic" << std::endl;
}

void test_OneMinMax_balanced(int k, int n, int coef, unsigned long seed, int nr_run, std::ostream &fout) {
    rand_gen.seed(seed);

    OneMinMaxBenchmark f(n);
    int pop_size = coef * f.PARETO_FRONT_SIZE;

    Balanced_NSGA<2> balanced_nsga(n, pop_size, f);

    auto start = high_resolution_clock::now();
    balanced_nsga.run();
    auto end = high_resolution_clock::now();

    auto rt = f.fitness_function_calls;
    auto duration = duration_cast<std::chrono::duration<double>>(end - start).count();

    fout << "OneMinMax," << n << "," << k << "," << pop_size << "," << nr_run << "," << seed
         << "," << rt << "," << duration << "," << balanced_nsga.total_time_non_dominated_sorting << ","
         << balanced_nsga.total_time_crowding_distance_computation << "," << balanced_nsga.total_time_selection << ", "
         << balanced_nsga.total_time_tiebreaker << ", balanced" << std::endl;
}

void test_LeadingOnesTrailingZeros_classic(int k, int n, int coef, unsigned long seed, int nr_run, std::ostream &fout) {
    rand_gen.seed(seed);

    LeadingOnesTrailingZeroBenchmark f(n);
    int pop_size = coef * f.PARETO_FRONT_SIZE;

    NSGA<2> standard_nsga(n, pop_size, f);

    auto start = high_resolution_clock::now();
    standard_nsga.run();
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<std::chrono::duration<double>>(end - start).count();
    auto rt = f.fitness_function_calls;
    fout << "LeadingOnesTrailingZeros," << n << "," << k << "," << pop_size << "," << nr_run << "," << seed
         << "," << rt << "," << duration << "," << standard_nsga.total_time_non_dominated_sorting << ","
         << standard_nsga.total_time_crowding_distance_computation << "," << standard_nsga.total_time_selection << ", "
         << standard_nsga.total_time_tiebreaker << ", classic" << std::endl;
}

void
test_LeadingOnesTrailingZeros_balanced(int k, int n, int coef, unsigned long seed, int nr_run, std::ostream &fout) {
    rand_gen.seed(seed);

    LeadingOnesTrailingZeroBenchmark f(n);
    int pop_size = coef * f.PARETO_FRONT_SIZE;

    Balanced_NSGA<2> balanced_nsga(n, pop_size, f);

    auto start = high_resolution_clock::now();
    balanced_nsga.run();
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<std::chrono::duration<double>>(end - start).count();

    auto rt = f.fitness_function_calls;
    fout << "LeadingOnesTrailingZeros," << n << "," << k << "," << pop_size << "," << nr_run << "," << seed
         << "," << rt << "," << duration << "," << balanced_nsga.total_time_non_dominated_sorting << ","
         << balanced_nsga.total_time_crowding_distance_computation << "," << balanced_nsga.total_time_selection << ", "
         << balanced_nsga.total_time_tiebreaker << ", balanced" << std::endl;
}

void test_OneJumpZeroJump_classic(int k, int n, int coef, unsigned long seed, int nr_run, std::ostream &fout) {
    rand_gen.seed(seed);

    OneJumpZeroJumpBenchmark f(n, k);
    int pop_size = coef * f.PARETO_FRONT_SIZE;

    NSGA<2> standard_nsga(n, pop_size, f);

    auto start = high_resolution_clock::now();
    standard_nsga.run();
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<std::chrono::duration<double>>(end - start).count();

    auto rt = f.fitness_function_calls;
    fout << "OneJumpZeroJump," << n << "," << k << "," << pop_size << "," << nr_run << "," << seed
         << "," << rt << "," << duration << "," << standard_nsga.total_time_non_dominated_sorting << ","
         << standard_nsga.total_time_crowding_distance_computation << "," << standard_nsga.total_time_selection << ", "
         << standard_nsga.total_time_tiebreaker << ", classic" << std::endl;
}

void test_OneJumpZeroJump_balanced(int k, int n, int coef, unsigned long seed, int nr_run, std::ostream &fout) {
    rand_gen.seed(seed);

    OneJumpZeroJumpBenchmark f(n, k);
    int pop_size = coef * f.PARETO_FRONT_SIZE;

    Balanced_NSGA<2> balanced_nsga(n, pop_size, f);
    balanced_nsga.b_type = 3; // in order to optimize rank sorting


    auto start = high_resolution_clock::now();
    balanced_nsga.run();
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<std::chrono::duration<double>>(end - start).count();
    auto rt = f.fitness_function_calls;
    fout << "OneJumpZeroJump," << n << "," << k << "," << pop_size << "," << nr_run << "," << seed
         << "," << rt << "," << duration << "," << balanced_nsga.total_time_non_dominated_sorting << ","
         << balanced_nsga.total_time_crowding_distance_computation << "," << balanced_nsga.total_time_selection << ", "
         << balanced_nsga.total_time_tiebreaker << ", balanced" << std::endl;
}


void test_4OneMinMax_classic(int k, int n, int coef, unsigned long seed, int nr_run, std::ostream &fout) {
    rand_gen.seed(seed);

    MOneMinMaxBenchmark<4> f(n);
    int pop_size = coef * f.PARETO_FRONT_SIZE;

    NSGA<4> standard_nsga(n, pop_size, f);
    standard_nsga.b_type = 1;
    standard_nsga.run();
    auto rt = f.fitness_function_calls;
    fout << "4OneMinMax," << n << "," << k << "," << pop_size << "," << nr_run << "," << seed
         << "," << rt << "," << "classic" << std::endl;
}

void test_4OneMinMax_balanced(int k, int n, int coef, unsigned long seed, int nr_run, std::ostream &fout) {
    rand_gen.seed(seed);

    MOneMinMaxBenchmark<4> f(n);
    int pop_size = coef * f.PARETO_FRONT_SIZE;

    Balanced_NSGA<4> balanced_nsga(n, pop_size, f);
    balanced_nsga.b_type = 1;

    auto start = high_resolution_clock::now();
    balanced_nsga.run();
    auto end = high_resolution_clock::now();


    auto duration = duration_cast<std::chrono::duration<double>>(end - start).count();
    auto rt = f.fitness_function_calls;
    fout << "4OneMinMax," << n << "," << k << "," << pop_size << "," << nr_run << "," << seed
         << "," << rt << "," << duration << "," << balanced_nsga.total_time_non_dominated_sorting << ","
         << balanced_nsga.total_time_crowding_distance_computation << "," << balanced_nsga.total_time_selection << ", "
         << balanced_nsga.total_time_tiebreaker << ", balanced" << std::endl;
}

int main() {
    /**
     * Running this file will generate exactly the same experimental data. Note that NMAX = 120 for OneJumpZeroJump, k = 3
     * is very slow, so we only ran it until NMAX = 50 and for 20 runs. All the other generate the exact same seed sequence as in the data
     * and in those conditions. If you want to just run a specific example, call the corresponding function with the right parameters
     * (the ones that are printed the data).
     */


    std::ofstream fout("experimental_extra_time_all.csv");
    fout
            << "Benchmark,n,k,Pop_size,Number_run,Seed,Runtime_Pareto_front,Total_Runtime(s),Total_Time_Spent_Non_Dominated_Sort(s),Total_Time_Spent_Crowding_Distance_Computation(s),Total_Time_Spent_Selection_Best_Crowding_Distance(s),Total_Time_Tiebreaker(s),Variant_NSGA\n";
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

        seed_generator.seed(1);
        for (int k = 1; k <= 1; k++) {
            for (int n = NMIN; n <= NMAX; n += 10) {
                for (int coef = 2; coef <= 16; coef *= 2) {
                    for (int nr_run = 1; nr_run <= RUNS + EXTRA_RUNS; nr_run++) {
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
        /**
         * In order to get the exact same data points, the seed needs to be the same as it was before (which was a slightly different testing environment.
         * This is why we need the discard (2400).
         */
        seed_generator.seed(2);

        for (int k = 3; k <= 3; k++) {
            for (int n = NMIN; n <= 50; n += 10) {
                for (int coef = 2; coef <= 8; coef *= 2) {
                    for (int nr_run = 1; nr_run <= RUNS + EXTRA_RUNS; nr_run++) {
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

    //4OneMinMax
    {

        seed_generator.seed(6);
        for (int k = 1; k <= 1; k++) {
            for (int n = NMIN; n <= NMAX; n += 10) {
                for (int coef = 2; coef <= 8; coef *= 2) {
                    for (int nr_run = 1; nr_run <= RUNS + EXTRA_RUNS; nr_run++) {
//                        //classic - does not converge in this example
//                        {
//                            auto seed = seed_generator();
//
//                            test_LeadingOnesTrailingZeros_classic(k, n, coef, seed, nr_run, fout);
//                        }
                        //balanced
                        {
                            auto seed = seed_generator();

                            test_4OneMinMax_balanced(k, n, coef, seed, nr_run, fout);
                        }
                    }
                }
            }
        }

    }
}