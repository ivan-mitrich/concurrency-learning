#include <iostream>
#include <thread>
#include <vector>
#include <fstream>
#include <chrono>
#include "Timer.h"
#include "FileHandle.h"

const int TEST_FUNCTIONS_LOOP_COUNTER = 10;

void single_thread_function(const std::vector<double>& test_vector);
void multiple_threads_function_mutex(const std::vector<double>& test_vector);
void multiple_threads_function_cond_var(const std::vector<double>& test_vector);
std::vector<double> create_test_vector();
void print_data(const std::vector<double>& data);

void print_consumed_time_wrapper(
        const std::vector<double>& wrapped_function_parameter,
        void (*wrapped_function)(const std::vector<double>&), 
        std::string wrapped_function_descr
        );

int main()
{
    std::vector<double> test_vector = create_test_vector();
    //print_consumed_time_wrapper(test_vector, single_thread_function, "single thread function");
    print_consumed_time_wrapper(test_vector, multiple_threads_function_mutex, "mutex multiple thread function");
    //print_consumed_time_wrapper(test_vector, multiple_threads_function_cond_var, "condition variable multiple thread function");
    return 0;
}

std::vector<double> create_test_vector() 
{
    const std::vector<double>::size_type VECTOR_SIZE = 10;
    std::vector<double> test_vector(VECTOR_SIZE);
    
    for(std::vector<double>::size_type i = 0; i < VECTOR_SIZE; ++i)  
    {
        test_vector[i] = i;
    }
    return test_vector;
}

void print_data(const std::vector<double>& data)
{
    std::cout << "Print function\n";
    std::cout << "Read items:\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    for (const auto& item : data)
    {
        std::cout << item << "\n";
    }
}

void single_thread_function(const std::vector<double>& test_vector)
{
    FileHandle file_handle("file1.txt");
    for (int i = 0; i < TEST_FUNCTIONS_LOOP_COUNTER; ++i)
    {      
        file_handle.print_data_to_file(test_vector);
        std::vector<double> data = file_handle.get_data_from_file();
        std::cout << "ITERATION = " << i << std::endl;
        print_data(data);
    }
}

void multiple_threads_function_mutex(const std::vector<double>& test_vector)
{
    FileHandle file_handle("file2.txt");
    
    int counter = 0;
    std::mutex m;

    std::thread t([&]() 
    {        
        for (; counter < TEST_FUNCTIONS_LOOP_COUNTER;)
        {    
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            m.lock();
            ++counter;
            if(counter % 2 == 0)
                std::cout << std::this_thread::get_id() << " " << counter << std::endl;    
            m.unlock();
        }
    });
   
    for (; counter < TEST_FUNCTIONS_LOOP_COUNTER;)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        m.lock();
        ++counter;
        if (counter % 2 != 0)
            std::cout << std::this_thread::get_id() << " " << counter << std::endl;    
        m.unlock();
    }
    t.join();
}

void multiple_threads_function_cond_var(const std::vector<double>& test_vector)
{
    //FileHandle file_handle("file3.txt");
    //for (int i = 0; i < TEST_FUNCTIONS_LOOP_COUNTER; ++i)
    //{
    //    file_handle.print_data_to_file(test_vector);
    //    std::vector<double> data = file_handle.get_data_from_file_mutex();
    //    print_data(data);
    //}
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
