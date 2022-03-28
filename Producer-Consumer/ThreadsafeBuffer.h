#ifndef THREADSAFEBUFFER_CPP
#define THREADSAFEBUFFER_CPP

#include <mutex>
#include <condition_variable>
#include <queue>

/*
* Simple threadsafe queue with int data. 
* Parametrization can be done via template mechanism.
* Here parametrization is not used because main goal of this simple class is learning how to synchronize two threads
*/

class ThreadsafeBuffer
{
private:
	// mutex to read/write storage data in different threads
	// mutable modificator is used to lock/unlock mutex in const member function empty()
	mutable std::mutex mutex;

	// mutex to read/write to console in different threads
	// mutable modificator is used to lock/unlock mutex in const member function empty()
	mutable std::mutex print_info_mutex;

	// cond_var is used to synchronize producer and consumer threads
	std::condition_variable cond_var;

	// storage where producer will put data and from which consumer will take data
	std::queue<int> storage;

	// is used to model fixed size buffer
	std::size_t storage_max_size;

public:
	explicit ThreadsafeBuffer(std::size_t buffer_maximum_elements = 1);

	void push(int data);
	
	// return by value because of simplicity of this class
	// in more complex projects should return pointer or use reference as out argument with void return type
	int pop();

	bool empty() const;


private:
	// used to watch the order of producing/consuming storage data in different threads
	void print_info(std::thread::id thread_id, std::string const& process_action, int processed_data) const;
};

#endif