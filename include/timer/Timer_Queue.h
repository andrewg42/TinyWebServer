#pragma once

#include <chrono>
#include <vector>
#include <set>
#include <memory>
#include <type_traits>
#include <utility>

#include <Config.h>
#include <timer/Timer.h>

namespace webserver {
namespace timer {

class Timer_Queue {
private:
    using Key_t = std::pair<Timer_Stamp_t, std::unique_ptr<Timer>>;
    
    std::set<Key_t> timer_mp;

public:
    // ctor
    explicit Timer_Queue();

    // dtor
    ~Timer_Queue();

    // add timer into container
    void add_timer();

    // remove timer from container
    void remove_timer();

    // alter timer in the container
    void update_timer();

    // get all expired timers 
    std::vector<Timer> tick(); 
};

} // namespace webserver::timer
} // namespace webserver