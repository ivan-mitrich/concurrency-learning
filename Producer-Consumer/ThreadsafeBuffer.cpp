#include "ThreadsafeBuffer.h"
#include <iostream>

ThreadsafeBuffer::ThreadsafeBuffer(std::size_t buffer_maximum_elements) : storage_max_size(buffer_maximum_elements)
{
	if (storage_max_size == 0)
	{
		storage_max_size = 1;
	}
}

// condition variable here is used to model fixed size buffer
// by not pushing data when storage size >= storage max size
void ThreadsafeBuffer::push(int data)
{
	std::unique_lock<std::mutex> lock(mutex);
	cond_var.wait(lock,
		[this]()
		{
			return storage.size() < storage_max_size;
		});
	storage.push(data);
	print_info(std::this_thread::get_id(), "produces", data);
	
	//notifying consumer that storage is not empty
	cond_var.notify_one();
}

int ThreadsafeBuffer::pop()
{
	std::unique_lock<std::mutex> lock(mutex);
	cond_var.wait(lock,
		[this]()
		{
			return storage.size() > 0;
		});
	int result = storage.front();
	storage.pop();
	print_info(std::this_thread::get_id(), "consumes", result);
	
	//notifing producer that storage.size was decreased. It allows producer to try to push new data to storage
	cond_var.notify_one();
	return result;
}

bool ThreadsafeBuffer::empty() const
{
	std::lock_guard<std::mutex> lock(mutex);
	return storage.empty();
}

void ThreadsafeBuffer::print_info(std::thread::id thread_id, std::string const& process_action, int processed_data) const 
{
	std::lock_guard<std::mutex> lock(print_info_mutex);
	std::cout << "ID#" << thread_id << " " << process_action << " " << processed_data << "\n";
}