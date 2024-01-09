#include <iostream>
#include "NSGA.h"
#include "Balanced_NSGA.h"
#include "OneMinMaxBenchmark.cpp"
#include "OneJumpZeroJumpBenchmark.cpp"
#include <json/json.h>


int main() {
//    for (int l = 50; l <= 100; l += 25) {
//        const int POP_size = 4 * l;
//        int k = 2;
//        const int n = l;
//        OneJumpZeroJumpBenchmark f(n, k);
//        NSGA try_1(n, POP_size, f);
//        std::cout << try_1.run() << " iterations\n";
//        std::cout << f.fitness_function_calls << "\n";
//
//        OneJumpZeroJumpBenchmark f2(n, k);
//
//        Balanced_NSGA try_2(n, POP_size, f2);
//        std::cout << try_2.run() << " iterations\n";
//        std::cout << f2.fitness_function_calls << "\n";
//
//        std::cout << "Difference is : " << f.fitness_function_calls - f2.fitness_function_calls << "; Percentage wise "
//                  << (double) f2.fitness_function_calls / f.fitness_function_calls;
//    }

    int k = 3;
    int n = 20;
    int POP_SIZE = 4*(n - 2*k + 3);

    OneJumpZeroJumpBenchmark f(n, k);
    NSGA ojzj_1(n, POP_SIZE, f);
    std::cout << ojzj_1.run() << " iterations\n";
    std::cout << f.fitness_function_calls << "\n";

//
//    OneJumpZeroJumpBenchmark f2(n, 1);
//    NSGA ojzj_2(n, POP_SIZE, f2);
//    std::cout << ojzj_2.run() << " iterations\n";
//    std::cout << f2.fitness_function_calls << "\n";
    return 0;
}
