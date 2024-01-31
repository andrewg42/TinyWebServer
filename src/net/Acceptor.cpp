#include <net/Acceptor.h>

namespace webserver {

namespace net {

namespace _detail {

_Acceptor<_detail::Proto_TCP>::_Acceptor() {
    sock_fd = ::socket(PF_INET, SOCK_STREAM, 0);
    assert(-1 != sock_fd);
}

_Acceptor<_detail::Proto_TCP>::~_Acceptor() {
    if(-1 != sock_fd) {
        ::close(sock_fd);
        //m_socket_fd = -1;
    }
}

_Acceptor<_detail::Proto_TCP>::_Acceptor(_Acceptor &&rhs) noexcept {
    sock_fd = rhs.sock_fd;
    rhs.sock_fd = -1;
}

_Acceptor<_detail::Proto_TCP> &_Acceptor<_detail::Proto_TCP>::operator=(_Acceptor &&rhs) noexcept {
    if(this != &rhs) {
        sock_fd = rhs.sock_fd;
        rhs.sock_fd = -1;
    }
    return *this;
}

void _Acceptor<_detail::Proto_TCP>::bind_addr(char const *ip, int port) {
    struct sockaddr_in s_addr;
    ::memset(&s_addr, 0, sizeof(struct sockaddr_in));

    s_addr.sin_family = AF_INET;
    s_addr.sin_addr.s_addr = ::inet_addr(ip);
    s_addr.sin_port = ::htons(port);

    if(-1 == ::bind(sock_fd,
                    reinterpret_cast<sockaddr*>(&s_addr), 
                    sizeof s_addr)) {
        // TODO: Handle ERROR
    }
}

void _Acceptor<_detail::Proto_TCP>::listen(int backlog) {
    if (-1 == ::listen(sock_fd, backlog)) {
        // TODO: Handle ERROR
    }
}

int _Acceptor<_detail::Proto_TCP>::accept_connection(sockaddr_in& cli_addr) {
    int cli_socket_fd = ::accept(sock_fd, reinterpret_cast<sockaddr*>(&cli_addr), &cli_addr_sz);

    if (-1 == cli_socket_fd) {
        // TODO: Handle ERROR
    }
    return cli_socket_fd;
}

} // namespace webserver::net::_detail

} // namespace webserver::net

} // namespace webserver