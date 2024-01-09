cmake_minimum_required(VERSION 3.27)
project(c___nsga)

set(CMAKE_CXX_STANDARD 17)

# Find JSONCpp package
find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP REQUIRED jsoncpp)

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
        NSGA.cpp)

# Include JSONCpp headers
target_include_directories(c___nsga PRIVATE ${JSONCPP_INCLUDE_DIRS})

# Link against JSONCpp library
target_link_libraries(c___nsga PRIVATE ${JSONCPP_LIBRARIES})
