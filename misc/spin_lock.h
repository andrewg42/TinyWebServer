#pragma once
#include <atomic>

namespace server {
namespace utils {

class Spin_Lock {
// ref: https://en.cppreference.com/w/cpp/atomic/atomic_flag
private:
    std::atomic_flag lck = ATOMIC_FLAG_INIT;

public:
    void lock() {
        while(lck.test_and_set(std::memory_order_acquire));
    }

    void unlock() {
        lck.clear(std::memory_order_release);
    }

};

} // namespace server::utils
} // namespace server