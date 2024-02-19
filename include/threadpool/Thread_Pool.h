#pragma once

#include <array>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <array>
#include <utils/Singleton.h>
#include <utils/Spin_Lock.h>
#include <utils/Blocking_Queue.h>

namespace webserver {
namespace threadpool {

template <class T, std::size_t N>
class Thread_Pool: public utils::Singleton<Thread_Pool<T, N>> {
private:
    std::size_t thread_number;
    std::array<T, N> pool;

public:
    // ctor
    Thread_Pool(std::size_t thread_num_)
    : thread_number(thread_num_) {}

    // dtor
    ~Thread_Pool();
    
    void run();

private:

};

} // namespace webserver::threadpool
} // namespace webserver