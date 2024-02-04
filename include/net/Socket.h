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

// RAII encapsulation for TCP server socket
class Serv_Sock: public utils::Noncopyable {
private:
    int sock_fd;

public:
    // ctor
    Serv_Sock();

    // dtor
    ~Serv_Sock();

    // move ctor
    Serv_Sock(Serv_Sock &&rhs) noexcept;

    // move assign
    Serv_Sock &operator=(Serv_Sock &&rhs) noexcept;

    // bind address
    // TODO: not need ip
    void bind_addr(char const *ip, int port);

    // 
    void listen(int backlog = 5);

    // interface for Acceptor
    int accept(sockaddr_in& cli_addr);
};

} // namespace webserver::net
} // namespace webserver