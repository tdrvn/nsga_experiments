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
    std::ofstream fout("experiment-onejumpzerojump.csv", std::ios::app);
    fout<<"Benchmark,n,k,Pop_size,Number_run,Seed(initial),Runtime_Pareto_front,Variant_NSGA";
    long long seed = 17948253413552098;

    //testing one jump zero jump
    {
        rand_gen.seed(seed);
        for(int k = 2; k <=4; k++){
            for(int n = 30; n <= 150; n+= 10){
                for(int coef = 2; coef <= 8; coef *= 2){
                    for(int nr_run = 1; nr_run <= 20; nr_run++){
                        OneJumpZeroJumpBenchmark f(n, k);
                        int pop_size = coef * f.PARETO_FRONT_SIZE;
                        NSGA<2> standard_nsga(n, pop_size, f);
                        auto rt = standard_nsga.run();
                        fout<<"OneJumpZeroJump,"<<n<<","<<k<<","<<pop_size<<","<<nr_run<<","<<seed<<","<<rt<<","<<"standard"<<std::endl;
                    }
                }
            }
        }


        for(int k = 2; k <=4; k++){
            for(int n = 30; n <= 150; n+= 10){
                for(int coef = 2; coef <= 8; coef *= 2){
                    for(int nr_run = 1; nr_run <= 20; nr_run++){
                        OneJumpZeroJumpBenchmark f(n, k);
                        int pop_size = coef * f.PARETO_FRONT_SIZE;
                        Balanced_NSGA<2> balanced_nsga(n, pop_size, f);
                        auto rt = balanced_nsga.run();
                        fout<<"OneJumpZeroJump,"<<n<<","<<k<<","<<pop_size<<","<<nr_run<<","<<seed<<","<<rt<<","<<"balanced"<<std::endl;
                    }
                }
            }
        }
    }
}
