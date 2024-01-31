#include <iostream>
#include <log/Log.h>
#include <string>
#include <chrono>

int main() {
    using dura_t = std::chrono::milliseconds;
    webserver::log::Log &log = webserver::log::Log::instance();
    log.set_level(webserver::log::Log_Level::trace);

    auto sender = [](dura_t t, int idx) {
        webserver::log::Log &log = webserver::log::Log::instance();
        for(int i{}; i<10; i++) {
            log.log_debug("thread {}: {}", idx, i);
            std::this_thread::sleep_for(t);
        }
    };

    dura_t dura1(400);
    dura_t dura2(200);

#define PER(f) f(1) f(2)
#define _FUNC(x) std::thread t##x (sender, dura##x, x);
    PER(_FUNC)
#undef _FUNC
#define _FUNC(x) t##x.join();
    PER(_FUNC)
#undef _FUNC
#undef PER

    log.stop();
    return 0;
}
