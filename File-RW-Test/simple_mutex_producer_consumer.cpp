#include "simple_mutex_producer_consumer.h"
#include <iostream>
#include <random>
#include <condition_variable>

const int simple_mutex::LOOP_COUNTER = 13;
const int simple_mutex::NOT_A_VALID_DATA = -111;
bool simple_mutex::is_produced = false;
bool simple_mutex::is_over = false;
std::mutex simple_mutex::mutex;
int simple_mutex::data_store = simple_mutex::NOT_A_VALID_DATA;
std::condition_variable data_cond;
bool can_produce = true;

void simple_mutex::producer_thread_function() {

	for (int i = 0; i < simple_mutex::LOOP_COUNTER; ++i)
	{
		std::unique_lock<std::mutex> lock(simple_mutex::mutex);
		//data_cond.wait(lock, [] { 
			//std::cout << "Producer wait-function checking ..." << std::endl;
		//	return !simple_mutex::is_produced; 
		//	});
		simple_mutex::data_store = produce_data();
		simple_mutex::is_produced = true;
		data_cond.notify_one();
	}
	
	is_over = true;
}

void simple_mutex::consumer_thread_function() {
	while (true)
	{	
		std::unique_lock<std::mutex> lock(simple_mutex::mutex);
		data_cond.wait(lock, [] { 
			//std::cout << "Consumer wait-function checking ..." << std::endl;
			return simple_mutex::is_produced; 
			});
		int data = simple_mutex::data_store;
		consume_data(data);
		simple_mutex::is_produced = false;
		
		lock.unlock();
		//data_cond.notify_one();
		if (is_over)
		{
			break;
		}
	}
}

int simple_mutex::produce_data()
{
	static int calling_counter = 0;
	int MIN = 0;
	int MAX = 1000;
	
	std::random_device                  rand_dev;
	std::mt19937                        generator(rand_dev());
	std::uniform_int_distribution<int>  distribution(MIN, MAX);
	
	int produced_data = distribution(generator);
	
	std::cout << " #" << calling_counter++ << " PRODUCED DATA : " << produced_data << std::endl;
	
	return produced_data;
}

void simple_mutex::consume_data(int data)
{
	static int calling_counter = 0;
	std::cout << " #" << calling_counter++ << " CONSUMED " << " DATA : " << data << std::endl;
}