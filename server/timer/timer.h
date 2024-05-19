#pragma once

#include <server/config.h>

namespace webserver {
namespace timer {

struct Timer {
    Timer_Stamp_t expired_time;
    Callback_t callback;

    // ctor
    explicit Timer(Timer_Stamp_t time, Callback_t cb_func)
    : expired_time(time), callback(std::move(cb_func)) {}

    // dtor
    ~Timer() = default;

    // move ctor
    Timer(Timer &&rhs) noexcept
    : expired_time(rhs.expired_time),
      callback(std::move(rhs.callback)) {}

    // move assign
    Timer &operator=(Timer &&rhs) noexcept {
        if(this != &rhs) {
            expired_time = rhs.expired_time;
            callback = std::move(rhs.callback);
        }
        return *this;
    }
};

} // namespace webserver::timer
} // namespace webserver
