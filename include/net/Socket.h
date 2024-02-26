#pragma once

#include <unistd.h>
#include <cstring>
#include <cassert>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <log/Log.h>

#include <utils/Noncopyable.h>

namespace webserver {
namespace net {

// RAII encapsulation for TCP server socket
class Socket: public utils::Noncopyable {
protected:
    int sock_fd;

public:
    // ctor
    explicit Socket(int fd): sock_fd(fd) {}

    // dtor
    ~Socket();

    // move ctor
    Socket(Socket &&rhs) noexcept;

    // move assign
    Socket &operator=(Socket &&rhs) noexcept;

    // bind address
    // no IP, so only support one NIC
    //void bind(int port);

    // TODO: support moew IP
    //void bind(char const *ip, int port);

    // listen for socket connections
    //void listen();

    // interface for Acceptor
    //int accept(sockaddr_in *p_clnt_addr);

    // close fd
    void close();

    // enable KEEPALIVE
    void set_keep_alive();

    // get sock_fd
    int get_fd() const { return sock_fd; }

private:
    // check if fd is closed
    bool is_closed() const { return -1 == sock_fd; }
};

} // namespace webserver::net
} // namespace webserver