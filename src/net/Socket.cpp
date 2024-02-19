#include <net/Socket.h>
#include <utility>
#include <log/Log.h>
#include <sys/socket.h>

namespace webserver {
namespace net {

constexpr static int BACKLOG = 4096;

Socket::~Socket() {
    close();
}

Socket::Socket(Socket &&rhs) noexcept {
    sock_fd = rhs.sock_fd;
    rhs.sock_fd = -1;
}

Socket &Socket::operator=(Socket &&rhs) noexcept {
    std::swap(sock_fd, rhs.sock_fd);
    return *this;
}

void Socket::close() {
    LOG_DEBUG("socket = {}, close()", sock_fd);
    if(!is_closed()) {
        if(-1 == ::close(sock_fd)) {
            LOG_ERROR("socket = {}, close()", sock_fd);
        }
    }
}

void Socket::set_keep_alive() {
    LOG_DEBUG("socket = {}, set_keep_alive()", sock_fd);
    uint32_t optval = 1;
    if(0 != ::setsockopt(sock_fd, SOL_SOCKET, SO_KEEPALIVE,
            &optval, static_cast<socklen_t>(sizeof optval))) {
        LOG_ERROR("socket = {}, set_keep_alive()", sock_fd);
    }
} 
} // namespace webserver::net
} // namespace webserver