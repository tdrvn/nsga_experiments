#include <iostream>
#include "NSGA.h"
#include "Balanced_NSGA.h"
#include "OneMinMaxBenchmark.cpp"
#include "OneJumpZeroJumpBenchmark.cpp"
#include <json/json.h>


int main() {
    int k = 2;
    int n = 10;
    int POP_SIZE = 4*(n - 2*k + 3);

    OneJumpZeroJumpBenchmark f(n, k);
    NSGA ojzj_1(n, POP_SIZE, f);
    std::cout << ojzj_1.run() << " iterations\n";
    std::cout << f.fitness_function_calls << "\n";


    OneJumpZeroJumpBenchmark f2(n, k);
    Balanced_NSGA ojzj_2(n, POP_SIZE, f2);
    std::cout << ojzj_2.run() << " iterations\n";
    std::cout << f2.fitness_function_calls << "\n";

    std::cout<<"Difference is "<<f.fitness_function_calls - f2.fitness_function_calls<<" , rapport is "<< (double) f2.fitness_function_calls / f.fitness_function_calls << std::endl;
    return 0;
}
