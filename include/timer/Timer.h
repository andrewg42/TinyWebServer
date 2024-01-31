#pragma once

#include <chrono>
#include <functional>

namespace webserver {

namespace timer {

struct Timer {
    using Key_Type = std::chrono::steady_clock::time_point;

    Key_Type expired_time;
    std::function<void()> cb_func; // TODO

    explicit Timer(Key_Type time): expired_time(time) {}

    bool operator<(Timer const &rhs) const { // for std::priority_queue
        return expired_time < rhs.expired_time;
    }
};

} // namespace webserver::timer

} // namespace webserver