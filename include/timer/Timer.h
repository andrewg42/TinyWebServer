#pragma once

#include <chrono>
#include <functional>

#include <Config.h>

namespace webserver {
namespace timer {

struct Timer {
    Timer_Stamp_t expired_time;
    std::function<void()> callback;

    explicit Timer(Timer_Stamp_t time, Callback_Func_t cb_func)
    : expired_time(time), callback(std::move(cb_func)) {}

    // for std::priority_queue
    bool operator<(Timer const &rhs) const {
        return expired_time < rhs.expired_time;
    }
};

} // namespace webserver::timer
} // namespace webserver