#include <server/config.h>
#include <server/net/channel.h>
#include <sys/epoll.h>

namespace webserver {
namespace net {

void Channel::handle_events(Timer_Stamp_t now) {
    handling = true;
    if ((revent & EPOLLHUP) && !(revent & EPOLLIN)) { // TCP closed
        handle_close();
    }

    if (revent & EPOLLERR) { // error
        handle_error();
    }

    if (revent & (EPOLLIN | EPOLLPRI | EPOLLRDHUP)) { // read
        handle_read();
    }

    if (revent & EPOLLOUT) { // write
        handle_write();
    }

    revent = 0;
    handling = false;
}

} // namespace webserver::net
} // namespace webserver