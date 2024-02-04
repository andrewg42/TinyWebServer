#pragma once

#include <unistd.h>
#include <vector>
#include <sys/epoll.h>

#include "Config.h"
#include <net/Channel.h>

namespace webserver {
namespace net {

// RAII encapsulation for epoll
class Reactor {
// ref: https://github.com/an-tao/trantor/blob/master/trantor/net/inner/poller/EpollPoller.h
private:
    int ep_fd;
    std::vector<struct epoll_event> event_list;

public:
    // ctor
    Reactor();

    // dtor
    ~Reactor();

    // add fd into epoll loop
    void ep_add(int fd);

    // modify fd in epoll loop
    void ep_mod(int fd);

    // remove fd from epoll loop
    void ep_del(int fd);

    // call epoll_wait() and get 
    std::vector<std::weak_ptr<Channel>> poll();
};

} // namespace webserver::net
} // namespace webserver