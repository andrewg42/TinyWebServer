#pragma once

#include <server/config.h>
#include <server/utils/noncopyable.h>
#include <server/net/socket.h>
#include <server/net/channel.h>
#include <sys/epoll.h>


namespace webserver {
namespace net {

class Event_Loop;

// server socket fd: only support:
// 1. listen socket connections
// 2. accept new connection (Http_Conn) on a socket
class Acceptor: public Socket {
private:
    Event_Loop *p_loop;

    // frequently used and will not be easily closed
    // directly use member variables
    Channel chan;

public:
    // ctor
    explicit Acceptor(Event_Loop *p_loop_, int port);

    // dtor
    ~Acceptor() = default;
    
    Channel *get_chan() { return &chan; }
    
private:
    void bind_and_listen(int port);

    void read_handler();

    // listen for socket connections and accept new connection on socket
    int accept(sockaddr_in *p_clnt_addr);
};

} // namespace webserver::net
} // namespace webserver