#pragma once

#include <sys/epoll.h>
#include <memory>
#include <vector>

#include <net/Socket.h>
#include "net/Channel.h"
#include <utils/Noncopyable.h>

namespace webserver {
namespace net {

class Event_Loop;
class Channel;

// client socket fd
class Http_Conn: public Socket, public std::enable_shared_from_this<Http_Conn> {
private:
    Event_Loop *p_loop;

    std::unique_ptr<Channel> p_chan;
    std::vector<char> read_buffer, write_buffer;

public:
    // ctor
    explicit Http_Conn(Event_Loop *p_loop_, int fd_);

    // dtor
    ~Http_Conn() = default;

    void init_chan();

    Channel *get_chan() { return p_chan.get(); }

private:
    void read_handler();
    void write_handler();
    void close_handler();
    void error_handler();
};

} // namespace webserver::net
} // namespace webserver