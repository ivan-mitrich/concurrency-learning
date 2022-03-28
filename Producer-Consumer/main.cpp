#include "ThreadsafeBuffer.h"
#include <thread>
#include <functional>
#include <string>
#include <iostream>

const std::size_t PRODUCER_STORAGE_CAPACITY = 2;
const int PRODUCED_DATA_AMOUNT = 10;
bool more_data_to_produce = true;
std::mutex print_info_mutex;

int create_data();
void producer(ThreadsafeBuffer& buffer);
void consumer(ThreadsafeBuffer& buffer);
void print_info(std::thread::id thread_id, std::string const & process_action, int processed_data);

int main()
{
	ThreadsafeBuffer buffer(PRODUCER_STORAGE_CAPACITY);
	std::thread producer_thread(producer, std::ref(buffer));
	std::thread consumer_thread(consumer, std::ref(buffer));
	producer_thread.join();
	consumer_thread.join();
	return 0;
}

int create_data()
{
	static int data = 0;
	return data++;
}

void producer(ThreadsafeBuffer& buffer)
{
	for (int i = 0; i < PRODUCED_DATA_AMOUNT; ++i)
	{
		int new_data = create_data();
		print_info(std::this_thread::get_id(), "produces", new_data);
		buffer.push(new_data);		
	}
	more_data_to_produce = false;
}

void consumer(ThreadsafeBuffer& buffer)
{
	while (true)
	{
		int data_to_process = buffer.pop();
		print_info(std::this_thread::get_id(), "consumes", data_to_process);		
		
		if (!more_data_to_produce && buffer.empty())
		{
			break;
		}
	}
}

void print_info(std::thread::id thread_id, std::string const& process_action, int processed_data)
{
	std::lock_guard<std::mutex> lock(print_info_mutex);
	std::cout << "ID#" << thread_id << " " << process_action << " " << processed_data << "\n";
}
