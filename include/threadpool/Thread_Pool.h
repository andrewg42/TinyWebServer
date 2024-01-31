#pragma once

#include <array>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <array>
#include <utils/Singleton.h>
#include <utils/Spin_Lock.h>

namespace webserver {

namespace threadpool {

template <class T, std::size_t N>
class Thread_Pool: public webserver::utils::Singleton<Thread_Pool<T, N>> {
private:
    std::size_t thread_number;
    std::array<T, N> pool;

public:
    Thread_Pool();
    ~Thread_Pool();
    
    void run();

private:

};

}

}