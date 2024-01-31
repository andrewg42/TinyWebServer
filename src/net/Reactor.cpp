#include <net/Reactor.h>

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <fcntl.h>

namespace webserver {

namespace net {

void Reactor::run() {
    // TODO
    while(is_running) {
        
    }
}

void Reactor::ep_add(int fd) {
    struct epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLET;
    epoll_ctl(ep_fd, EPOLL_CTL_ADD,fd, &event);
}

void Reactor::ep_remove(int fd) {
    epoll_ctl(ep_fd, EPOLL_CTL_DEL, fd, NULL);
    close(fd);
}

void Reactor::ep_mode(int fd) {
    // TODO
}

} // namespace webserver::net

} // namespace webserver