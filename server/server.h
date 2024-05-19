#pragma once

#include <server/utils/singleton.h>
#include <server/log/log.h>
#include <server/net/event_loop.h>
#include <server/net/channel.h>


namespace webserver {

struct Webserver { // do not use singleton! log::Log is singleton. Webserver need a shorter lifetime
public:
    Webserver(int port_): port(port_) {}
    void start() {
        net::Event_Loop event_loop(port);
        
        event_loop.loop();
    }
    
private:
    int port;
};

} // namespace webserver