#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <fstream>
#include <chrono>
#include "Timer.h"
#include "FileHandle.h"

void single_thread_function(const std::vector<double>& test_vector);
void multiple_threads_function_mutex(const std::vector<double>& test_vector);
void multiple_threads_function_cond_var(const std::vector<double>& test_vector);
std::vector<double> create_test_vector();

void print_consumed_time_wrapper(
        const std::vector<double>& wrapped_function_parameter,
        void (*wrapped_function)(const std::vector<double>&), 
        std::string wrapped_function_descr
        );

std::mutex mutex;
int counter = 0;
const int LOOP_COUNTER = 10;
void print_even();
void print_odd();

int main()
{
/*    std::vector<double> test_vector = create_test_vector();
    print_consumed_time_wrapper(test_vector, single_thread_function, "single thread function");
    print_consumed_time_wrapper(test_vector, multiple_threads_function_mutex, "mutex multiple thread function");
    print_consumed_time_wrapper(test_vector, multiple_threads_function_cond_var, "condition variable multiple thread function");
  */
    //trying to print even/odd numbers in different threads in turn
    std::thread t_even(print_even);
    std::thread t_odd(print_odd);

    t_even.join();
    t_odd.join();

    return 0;
}

void print_even() 
{
	for(; counter < LOOP_COUNTER;)
	{
        if(counter % 2 == 0)
        {
            mutex.lock();
            std::cout << "EVEN THREAD : "  << std::this_thread::get_id() << " " << counter << std::endl;
            ++counter;
            mutex.unlock();

    	}
    }
}

void print_odd() 
{
	for(; counter < LOOP_COUNTER;)
    {
        if(counter % 2 != 0)
        {
            mutex.lock();
            std::cout << "ODD THREAD : "  << std::this_thread::get_id() << " " << counter << std::endl;
            ++counter;
            mutex.unlock();
    	}
	}
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

}

void multiple_threads_function_mutex(const std::vector<double>& test_vector)
{

}

void multiple_threads_function_cond_var(const std::vector<double>& test_vector)
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
