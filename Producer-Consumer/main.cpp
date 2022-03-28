#include "ThreadsafeBuffer.h"
#include <thread>
#include <functional>
#include <string>
#include <iostream>

// threadsafe buffer size
const std::size_t PRODUCER_STORAGE_CAPACITY = 7;

// how many data to create
const int PRODUCED_DATA_AMOUNT = 10;

// flag is used to let consumer get all produced data if consumer works faster than producer
bool more_data_to_produce = true;

// simple function to create data
int create_data();

// producer function
void producer(ThreadsafeBuffer& buffer);

// consumer function
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
		
		// buffer.empty() check is used to let consume last data chunk
		if (!more_data_to_produce && buffer.empty())
		{
			break;
		}
	}
}

/*
	Possible output:

	ID#12748 produces 0
	ID#12748 produces 1
	ID#12748 produces 2
	ID#12748 produces 3
	ID#12748 produces 4
	ID#12748 produces 5
	ID#12748 produces 6
	ID#12748 produces 0
	ID#10048 consumes 1
	ID#10048 consumes 2
	ID#10048 consumes 3
	ID#10048 consumes 4
	ID#10048 consumes 5
	ID#10048 consumes 6
	ID#12748 produces 7
	ID#12748 produces 8
	ID#12748 produces 9
	ID#10048 consumes 7
	ID#10048 consumes 8
	ID#10048 consumes 9

*/