#include <iostream>
#include <timer/Timer_Queue.h>

#define TO_LONG(x) std::chrono::duration_cast<std::chrono::nanoseconds>(x.time_since_epoch()).count()
int main() {
    using namespace server::timer;
    Timer_Queue tq;

    std::function<void()> cb = nullptr;
    auto tmp = std::chrono::steady_clock::now();

    for(int i{}; i<10; i++) {
        tmp = std::chrono::steady_clock::now();
        tq.add_timer(tmp, std::move(cb));
        std::cout << "add time: " << TO_LONG(tmp) << '\n';
    }

    auto vec = tq.tick(std::chrono::steady_clock::now());

    std::cout << "finish tick\n";
    for(auto &elem:vec) {
        std::cout << "remove time: " << TO_LONG(elem->expired_time) << '\n';
    }

    std::cout << "size of timer queue: " << tq.size() << '\n';
    return 0;
}
