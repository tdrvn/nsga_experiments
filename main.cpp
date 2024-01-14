#include <iostream>
#include "NSGA.h"
#include "NSGA.cpp"
#include "Balanced_NSGA.h"
#include "Balanced_NSGA.cpp"
#include "OneMinMaxBenchmark.cpp"
#include "OneJumpZeroJumpBenchmark.cpp"
#include "LeadingOnesTrailingZeroBenchmark.cpp"
#include "mOneMinMaxBenchmark.cpp"
#include <json/json.h>
#include <stdio.h>



int main() {

    int n = 80;
    int N =  (n/2 + 1) * (n/2 + 1) + 4 * (n/2 + 1);

//    MOneMinMaxBenchmark<4> f1(n);
//    NSGA<4> t_1(n, N, f1);
//    t_1.b_type = 1;
//    std::cout<<"Nr. iterations:"<<t_1.run()<<"\n";
//    std::cout<<"Nr. runtime: "<<f1.fitness_function_calls<<"\n";


    MOneMinMaxBenchmark<4> f2(n);
    Balanced_NSGA<4> t_2(n, N, f2);
    t_2.b_type = 1;
    std::cout<<"Nr. iterations:"<<t_2.run()<<"\n";
    std::cout<<"Nr. runtime: "<<f2.fitness_function_calls<<"\n";
    return 0;
}
