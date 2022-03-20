#include <iostream>
#include <thread>
#include <vector>
#include <fstream>
#include <chrono>
#include "Timer.h"
#include "FileHandle.h"

void single_thread_function(const std::vector<double>& test_vector);
void multiple_threads_function(const std::vector<double>& test_vector);
std::vector<double> create_test_vector();

void print_consumed_time_wrapper(
        const std::vector<double>& wrapped_function_parameter,
        void (*wrapped_function)(const std::vector<double>&), 
        std::string wrapped_function_descr
        );

int main()
{
    std::vector<double> test_vector = create_test_vector();
    print_consumed_time_wrapper(test_vector, single_thread_function, "single thread function");
    print_consumed_time_wrapper(test_vector, multiple_threads_function, "multiple thread function");

    return 0;
}

std::vector<double> create_test_vector() 
{
    const std::vector<double>::size_type VECTOR_SIZE = 10000;
    std::vector<double> test_vector(VECTOR_SIZE);
    
    for(std::vector<double>::size_type i = 0; i < VECTOR_SIZE; ++i)  
    {
        test_vector[i] = i;
    }
    return test_vector;
}

void single_thread_function(const std::vector<double>& test_vector)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

void multiple_threads_function(const std::vector<double>& test_vector)
{

}

void print_consumed_time_wrapper(
        const std::vector<double>& wrapped_function_parameter,
        void (*wrapped_function)(const std::vector<double>&), 
        std::string wrapped_function_descr
        )
{
    Timer timer;
    wrapped_function(wrapped_function_parameter);
    double consumed_time = timer.elapsed();
    std::cout << "Time consumed by " << wrapped_function_descr
        << " = " << consumed_time << " seconds\n";

}
