#include <net/Reactor.h>

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <sys/epoll.h>
#include <unistd.h>

#include <log/Log.h>

namespace webserver {
namespace net {

Reactor::Reactor()
    : ep_fd(::epoll_create1(EPOLL_CLOEXEC)),
      event_list(16){
    if(-1 == ep_fd) {
        LOG_ERROR("epoll_create()");
    }
}

Reactor::~Reactor() {
    ::close(ep_fd);
}

void Reactor::ep_add(int fd) {
    struct epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLET;
    epoll_ctl(ep_fd, EPOLL_CTL_ADD, fd, &event);
}

void Reactor::ep_mod(int fd) {

}

void Reactor::ep_del(int fd) {
    epoll_ctl(ep_fd, EPOLL_CTL_DEL, fd, NULL);
    // TODO close fd;
}

std::vector<std::weak_ptr<Channel>> Reactor::poll() {
    int num = ::epoll_wait(ep_fd, event_list.data(), event_list.size(), 0);

}

} // namespace webserver::net
} // namespace webserver