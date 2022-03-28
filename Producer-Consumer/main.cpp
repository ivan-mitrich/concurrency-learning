#include "ThreadsafeBuffer.h"
#include <thread>
#include <functional>
#include <string>
#include <iostream>

const std::size_t PRODUCER_STORAGE_CAPACITY = 1;
const int PRODUCED_DATA_AMOUNT = 10;
bool more_data_to_produce = true;
std::mutex print_info_mutex;

int create_data();
void producer(ThreadsafeBuffer& buffer);
void consumer(ThreadsafeBuffer& buffer);

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
		buffer.push(new_data);		
	}
	more_data_to_produce = false;
}

void consumer(ThreadsafeBuffer& buffer)
{
	while (true)
	{
		int data_to_process = buffer.pop();
		if (!more_data_to_produce && buffer.empty())
		{
			break;
		}
	}
}
