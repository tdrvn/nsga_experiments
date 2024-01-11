#include <iostream>
#include "NSGA.h"
#include "Balanced_NSGA.h"
#include "OneMinMaxBenchmark.cpp"
#include "OneJumpZeroJumpBenchmark.cpp"
#include <json/json.h>
#include <stdio.h>

int main() {
// test number of iterations to reach inner pareto front
    freopen("logs-both_experiments.out", "w", stdout);

    for(int i = 25; i < 150; i+=25) {
        for(int k = 2; k <= 4; k++) {
            int n = i;
            int POP_SIZE = 4 * (n + 1);
            std::cerr << "We are at step " << i << std::endl;
            std::cout << "\nn = " << n << ", k = " << k << ", N = " << POP_SIZE << "\n";
            std::cout<<"Standard version:\n";
            OneMinMaxBenchmark f(n);
            NSGA t_1(n, POP_SIZE, f);
            std::cout << t_1.run() << " iterations for OneMinMax with parameters (n, N)\n";
            std::cout << f.fitness_function_calls << " fitness function calls\n";


            OneJumpZeroJumpBenchmark f2(n, k);
            NSGA t_2(n, POP_SIZE, f2);
            int iter_tot = t_2.run();
            std::cout << iter_tot << " iterations for OneJumpZeroJump with (n, k, N)\n";
            std::cout << f2.fitness_function_calls << "fitness function calls\n";

            std::cout << "Iter to reach inner PF: " << t_2.iter_reach_inner << "\n";
            std::cout << "Iter to reach outer PF from inner PF: " << iter_tot - t_2.iter_reach_inner << "\n";
            std::cout << "Expected number of iter for 3rd stage(from paper): " << 2.0 * 2.7 * pow(n, k) << "\n";
            //std::cout<<"Difference is "<<f.fitness_function_calls - f2.fitness_function_calls<<" , rapport is "<< (double) f2.fitness_function_calls / f.fitness_function_calls << std::endl;

            std::cout<<"Balanced version:\n";
            OneMinMaxBenchmark f3(n);
            NSGA t_3(n, POP_SIZE, f3);
            std::cout << t_3.run() << " iterations for OneMinMax with parameters (n, N)\n";
            std::cout << f3.fitness_function_calls << " fitness function calls\n";


            OneJumpZeroJumpBenchmark f4(n, k);
            NSGA t_4(n, POP_SIZE, f4);
            int iter_tot_4 = t_4.run();
            std::cout << iter_tot_4 << " iterations for OneJumpZeroJump with (n, k, N)\n";
            std::cout << f4.fitness_function_calls << "fitness function calls\n";

            std::cout << "Iter to reach inner PF: " << t_4.iter_reach_inner << "\n";
            std::cout << "Iter to reach outer PF from inner PF: " << iter_tot_4 - t_4.iter_reach_inner << "\n";
            std::cout << "Expected number of iter for 3rd stage(from paper): " << 2.0 * 2.7 * pow(n, k) << "\n";
            //std::cout<<"Difference is "<<f.fitness_function_calls - f2.fitness_function_calls<<" , rapport is "<< (double) f2.fitness_function_calls / f.fitness_function_calls << std::endl;

        }
    }
    return 0;
}
