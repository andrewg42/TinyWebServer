#include <timer/Timer_Queue.h>
#include <chrono>
#include <iterator>
#include <memory>
#include "Config.h"

namespace webserver {
namespace timer {

Timer_Queue::~Timer_Queue() {
    for(auto it=timer_mp.begin(); it!=timer_mp.end(); ) it = timer_mp.erase(it);
}

void Timer_Queue::add_timer(Timer &&timer) {
    timer_mp.insert(Key_t(std::move(timer)));
}

void Timer_Queue::remove_timer() {
    // TODO
}


std::vector<std::shared_ptr<Timer>> Timer_Queue::tick(Timer_Stamp_t time_stamp) {
    Key_t sen(time_stamp, nullptr);
    auto end = timer_mp.lower_bound(sen);

    std::vector<std::shared_ptr<Timer>> ret;
    for(auto it=timer_mp.begin(); it!=end; ) {
        ret.push_back(it->p_timer);
        it = timer_mp.erase(it);
    }

    return ret;
}

} // namespace webserver::timer
} // namespace webserver