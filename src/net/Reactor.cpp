#include <net/Reactor.h>

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>

#include <log/Log.h>

namespace webserver {
namespace net {

Reactor::Reactor() {
    if(-1 == (ep_fd = ::epoll_create1(EPOLL_CLOEXEC))) {
        LOG_DEBUG("epoll_create() error");
    }
}

Reactor::~Reactor() {
    ::close(ep_fd);
}

void Reactor::add(int fd) {
    struct epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLET;
    epoll_ctl(ep_fd, EPOLL_CTL_ADD, fd, &event);
}

void Reactor::remove(int fd) {
    epoll_ctl(ep_fd, EPOLL_CTL_DEL, fd, NULL);
    // TODO close fd;
}


} // namespace webserver::net
} // namespace webserver