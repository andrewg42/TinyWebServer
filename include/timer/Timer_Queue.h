#pragma once

#include <chrono>
#include <vector>
#include <set>
#include <memory>
#include <type_traits>
#include <utility>
#include <functional>

#include <Config.h>
#include <timer/Timer.h>

namespace webserver {
namespace timer {

struct Key_t {
    Timer_Stamp_t stamp;
    std::unique_ptr<Timer> p_timer;

    explicit Key_t(Timer &&timer)
    : stamp(timer.expired_time), p_timer(std::make_unique<Timer>(std::move(timer))) {}

    explicit Key_t(Timer_Stamp_t timer_stamp, Callback_Func_t cb_func)
    : stamp(timer_stamp), p_timer(std::make_unique<Timer>(timer_stamp, cb_func)) {}

    // for sentinel
    explicit Key_t(Timer_Stamp_t timer_stamp, std::nullptr_t)
    : stamp(timer_stamp), p_timer(nullptr) {}
};

constexpr bool operator<(Key_t const &lhs, Key_t const &rhs) {
    if(lhs.stamp != rhs.stamp) [[likely]] { return lhs.stamp < rhs.stamp; }
    else [[unlikely]] { return lhs.p_timer > rhs.p_timer; }
}

class Timer_Queue {
private:
    std::set<Key_t> timer_mp;

public:
    // ctor
    Timer_Queue() = default;

    // dtor
    ~Timer_Queue();

    // add timer into container
    void add_timer(Timer_Stamp_t stamp, Callback_Func_t &&cb);

    // remove timer from container
    void remove_timer();

    // get all expired timers 
    std::vector<std::unique_ptr<Timer>> tick(Timer_Stamp_t time_stamp); 

    std::size_t const size() const { return timer_mp.size(); } 
};

} // namespace webserver::timer
} // namespace webserver