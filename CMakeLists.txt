cmake_minimum_required(VERSION 3.20)
project(c___nsga)

set(CMAKE_CXX_STANDARD 17)


# Add your source files
add_executable(c___nsga main.cpp
        NSGA.h
        Individual.h
        Benchmark.h
        globals.cpp
        globals.h
        OneMinMaxBenchmark.cpp
        OneJumpZeroJumpBenchmark.cpp
        Balanced_NSGA.h
        Balanced_NSGA.cpp
        NSGA.cpp
        LeadingOnesTrailingZeroBenchmark.cpp
        mOneMinMaxBenchmark.cpp
)

add_compile_options(-O3)