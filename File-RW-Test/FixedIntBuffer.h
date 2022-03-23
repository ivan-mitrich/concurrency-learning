#ifndef FIXEDINTBUFFER_H
#define FIXEDINTBUFFER_H

#include <cstddef>
#include <queue>
#include <mutex>
#include <condition_variable>

class FixedIntBuffer {
    private:
        std::queue<int> buffer;
        std::size_t buffer_size;
        std::mutex buffer_mutex;
        std::condition_variable buffer_cond_var;
    public:
        explicit FixedIntBuffer(std::size_t size_of_buffer = 1);
        void push(int value);
        int pop();
};


#endif
