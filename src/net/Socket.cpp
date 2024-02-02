#include <net/Socket.h>
#include <utility>
#include <log/Log.h>

namespace webserver {
namespace net {

Serv_Sock::Serv_Sock() {
    sock_fd = ::socket(PF_INET, SOCK_STREAM, 0);
    assert(-1 != sock_fd);
}

Serv_Sock::~Serv_Sock() {
    if(-1 != sock_fd) {
        ::close(sock_fd);
    }
}

Serv_Sock::Serv_Sock(Serv_Sock &&rhs) noexcept {
    sock_fd = rhs.sock_fd;
    rhs.sock_fd = -1;
}

Serv_Sock &Serv_Sock::operator=(Serv_Sock &&rhs) noexcept {
    std::swap(sock_fd, rhs.sock_fd);
    return *this;
}

void Serv_Sock::bind_addr(char const *ip, int port) {
    struct sockaddr_in s_addr;
    ::memset(&s_addr, 0, sizeof(struct sockaddr_in));

    s_addr.sin_family = AF_INET;
    s_addr.sin_addr.s_addr = ::inet_addr(ip);
    s_addr.sin_port = ::htons(port);

    if(-1 == ::bind(sock_fd,
                    reinterpret_cast<sockaddr*>(&s_addr), 
                    sizeof s_addr)) {
        LOG_DEBUG("bind() error")
    }
}

void Serv_Sock::listen(int backlog) {
    if (-1 == ::listen(sock_fd, backlog)) {
        LOG_DEBUG("listen() error");
    }
}

int Serv_Sock::accept(sockaddr_in& cli_addr) {
    socklen_t cli_addr_sz = sizeof(struct sockaddr_in);
    int cli_Serv_Sock_fd = ::accept4(sock_fd, reinterpret_cast<sockaddr*>(&cli_addr),
                                &cli_addr_sz, SOCK_NONBLOCK | SOCK_CLOEXEC);

    if (-1 == cli_Serv_Sock_fd) {
        LOG_DEBUG("accept() error")
    }
    return cli_Serv_Sock_fd;
}

} // namespace webserver::net
} // namespace webserver