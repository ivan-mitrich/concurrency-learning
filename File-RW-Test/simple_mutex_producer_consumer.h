#ifndef SIMPLE_MUTEX_PRODUCER_CONSUMER_H
#define SIMPLE_MUTEX_PRODUCER_CONSUMER_H

#include <mutex>

namespace simple_mutex {
	extern const int LOOP_COUNTER;
	
	extern bool is_produced;
	extern bool is_over;
	extern std::mutex mutex;
	extern int data_store;
	
	void producer_thread_function();
	int produce_data();

	void consumer_thread_function();
	void consume_data(int data);
}

#endif