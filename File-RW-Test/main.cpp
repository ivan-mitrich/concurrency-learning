#include "simple_mutex_producer_consumer.h"
#include <thread>

int main()
{
    std::thread producer_thread(simple_mutex::producer_thread_function);
    std::thread consumer_thread(simple_mutex::consumer_thread_function);
    producer_thread.join();
    consumer_thread.join();
    return 0;
}
