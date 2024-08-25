#include <server/config.h>
#include <server/timer/timer.h>
#include <server/timer/timer_queue.h>

namespace server {
namespace timer {

Timer_Queue::~Timer_Queue() {
  for (auto it = timer_mp.begin(); it != timer_mp.end();) {
    it = timer_mp.erase(it);
  }
}

void Timer_Queue::add_timer(Timer_Stamp_t stamp, Callback_t &&cb) {
  timer_mp.insert(Key_t(stamp, std::move(cb)));
}

void Timer_Queue::remove_timer() {
  // TODO
}

std::vector<std::unique_ptr<Timer>>
Timer_Queue::tick(Timer_Stamp_t time_stamp) {
  Key_t sen(time_stamp, nullptr);
  auto end = timer_mp.lower_bound(sen);

  std::vector<std::unique_ptr<Timer>> ret;
  for (auto it = timer_mp.begin(); it != end;) {
    ret.emplace_back(std::move(timer_mp.extract(it++).value().p_timer));
  }

  return ret;
}

} // namespace timer
} // namespace server
