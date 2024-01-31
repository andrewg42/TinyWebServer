#pragma once

#include <unistd.h>
#include <cstring>
#include <cassert>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <utils/Noncopyable.h>
#include <net/Reactor.h>

namespace webserver {

namespace net {

namespace _detail {

struct Proto_TCP;
struct Proto_UDP;

template <class T>
class _Acceptor {};

// Acceptor for TCP connection
template <>
class _Acceptor<_detail::Proto_TCP>: public utils::Noncopyable {
private:
    int sock_fd;
    socklen_t cli_addr_sz = sizeof(struct sockaddr_in);

public:
    _Acceptor();
    ~_Acceptor();
    _Acceptor(_Acceptor &&rhs) noexcept;
    _Acceptor &operator=(_Acceptor &&rhs) noexcept;

    void bind_addr(char const *ip, int port);
    void listen(int backlog = 5);
    int accept_connection(sockaddr_in& cli_addr);
};

// TODO: implement of UDP Acceptor
template <>
class _Acceptor<_detail::Proto_UDP>: public utils::Noncopyable {

};

} // namespace webserver::net::_detail

using TCP_Acceptor = _detail::_Acceptor<_detail::Proto_TCP>;
using UDP_Acceptor = _detail::_Acceptor<_detail::Proto_UDP>;

} // namespace webserver::net

} // namespace webserver