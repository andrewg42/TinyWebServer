#pragma once

#include <memory>

#include <net/Reactor.h>
#include <utils/Noncopyable.h>

namespace webserver {
namespace net {

class Event_Loop: public utils::Noncopyable {
private:
    bool is_running;
    std::unique_ptr<Reactor> p_reactor;

public:
    // ctor
    Event_Loop();

    // dtor
    ~Event_Loop();

    // call epoll_wait() in loop and handle evnets
    void loop();


};

} // namespace webserver::net
} // namespace webserver