#pragma once

#include <unistd.h>
#include <sys/epoll.h>

namespace webserver {
namespace net {

// RAII encapsulation for epoll
class Reactor {
// ref: https://github.com/an-tao/trantor/blob/master/trantor/net/inner/poller/EpollPoller.h
private:
    int ep_fd;

public:
    // ctor
    Reactor();

    // dtor
    ~Reactor();

    // add fd into epoll loop
    void add(int fd);

    // remove file description from epoll loop
    void remove(int fd);

};

} // namespace webserver::net
} // namespace webserver