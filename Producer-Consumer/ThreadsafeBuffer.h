#ifndef THREADSAFEBUFFER_CPP
#define THREADSAFEBUFFER_CPP

#include <mutex>
#include <condition_variable>
#include <queue>

class ThreadsafeBuffer
{
private:
	mutable std::mutex mutex;
	std::condition_variable cond_var;
	std::queue<int> storage;
	std::size_t storage_max_size;

public:
	explicit ThreadsafeBuffer(std::size_t buffer_maximum_elements = 1);

	void push(int data);
	int pop();

	bool empty() const;

};

#endif