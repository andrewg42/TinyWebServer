#include <net/Event_Loop.h>

namespace webserver {
namespace net {

void Event_Loop::loop() {
    is_running = true;

    while(is_running) {
        auto ready_channels = p_reactor->poll();
    }
}

} // namespace webserver::net
} // namespace webserver
