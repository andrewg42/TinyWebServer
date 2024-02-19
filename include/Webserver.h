#pragma once

#include <net/Event_Loop.h>
#include <net/Channel.h>

#include <utils/Singleton.h>
#include "log/Log.h"

namespace webserver {

class Webserver { // do not use singleton! log::Log is singleton. Webserver need a shorter lifetime
private:
    int port;

public:
    Webserver(int port_): port(port_) {}
    ~Webserver() = default;

    void start() {
        net::Event_Loop event_loop(port);
        
        event_loop.loop();
    }
};

} // namespace webserver