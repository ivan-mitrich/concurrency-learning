#include "ThreadsafeBuffer.h"

ThreadsafeBuffer::ThreadsafeBuffer(std::size_t buffer_maximum_elements) : storage_max_size(buffer_maximum_elements)
{

}

void ThreadsafeBuffer::push(int data)
{
	std::lock_guard<std::mutex> lock(mutex);
	storage.push(data);
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
	return result;
}

bool ThreadsafeBuffer::empty() const
{
	std::lock_guard<std::mutex> lock(mutex);
	return storage.empty();
}
