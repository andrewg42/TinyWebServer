#pragma once

#include <chrono>
#include <functional>

#include <Config.h>

namespace webserver {
namespace timer {

struct Timer {
    Timer_Stamp_t expired_time;
    Callback_Func_t callback;

    explicit Timer(Timer_Stamp_t time, Callback_Func_t cb_func)
    : expired_time(time), callback(std::move(cb_func)) {}

    Timer(Timer &&rhs) noexcept
    : expired_time(rhs.expired_time),
      callback(std::move(rhs.callback)) {}

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
