#include <iostream>
#include "NSGA.h"
#include "NSGA.cpp"
#include "Balanced_NSGA.h"
#include "Balanced_NSGA.cpp"
#include "OneMinMaxBenchmark.cpp"
#include "OneJumpZeroJumpBenchmark.cpp"
#include "LeadingOnesTrailingZeroBenchmark.cpp"
#include <json/json.h>
#include <stdio.h>


/**
 * Todo:
 * - make lotz
 * - make multiple nsga
 * - test
 *
 */
int main() {

    int n = 200;
    int N = 5 * (n + 1);

    LeadingOnesTrailingZeroBenchmark f1(n);
    NSGA<2> t_1(n, N, f1);
    std::cout<<"Nr. iterations:"<<t_1.run()<<"\n";
    std::cout<<"Nr. runtime: "<<f1.fitness_function_calls<<"\n";


    LeadingOnesTrailingZeroBenchmark f2(n);
    Balanced_NSGA<2> t_2(n, N, f2);
    std::cout<<"Nr. iterations:"<<t_2.run()<<"\n";
    std::cout<<"Nr. runtime: "<<f2.fitness_function_calls<<"\n";
    return 0;
}
