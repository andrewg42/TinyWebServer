#pragma once

#include <chrono>
#include <queue>
#include <type_traits>

#include <timer/Timer.h>
#include <utility>

namespace webserver {

namespace timer {

class Time_Heap {
private:
    std::size_t capacity;
    std::priority_queue<Timer> heap;

public:
    // TODO
    explicit Time_Heap() {}

    // for both lvalue and rvalue
    template <class T>
    void push(T &&timer) {
        heap.push(std::forward<T>(timer));
    }

    void remove() {
        heap.pop();
    }
};

} // namespace webserver::timer

} // namespace webserver