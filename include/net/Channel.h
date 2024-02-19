#pragma once

#include <cstdint>
#include <memory>
#include <Config.h>
#include <net/Socket.h>
#include <utils/Noncopyable.h>
#include <log/Log.h>

namespace webserver {
namespace net {

class Event_Loop;
class Http_Conn;

enum class Channel_Status: unsigned char { removed = 0, added };

class Channel: utils::Noncopyable {
private:
    Event_Loop *p_loop;

    // intermediate layer added just because we don’t know when client socket will be destroyed
    std::weak_ptr<Http_Conn> wp_conn;
    int fd;

    uint32_t event;
    uint32_t revent; // received event mask
    Channel_Status status;

#define PER(f) \
    f(read) \
    f(write) \
    f(close) \
    f(error)

#define FUNC_(x) Callback_t x##_handler;
    PER(FUNC_)
#undef FUNC_

public:
    // ctor
    // only initialized by Acceptor and Http_Conn
    explicit Channel(Event_Loop *p_loop_, int fd_, uint32_t event_)
    : p_loop(p_loop_), fd(fd_), revent{}, event(event_), status(Channel_Status::removed) {}

    // dtor
    ~Channel() = default;

    // operators for fd (fxxk OOP)
    int get_fd() const { return fd; }
    void set_fd(int const fd_) { fd = fd_; }

    // operators for wp_conn
    auto get_holder() -> std::shared_ptr<Http_Conn> { return wp_conn.lock(); }
    void set_holder(std::shared_ptr<Http_Conn> p_conn) { wp_conn = p_conn; }

    // operators for event and revent
    uint32_t get_event() const { return event; }
    void set_revent(uint32_t revent_) { revent = revent_; }

    // operators for status
    Channel_Status get_status() const { return status; }
    void set_status(int status_) { status = static_cast<Channel_Status>(status_); }
    void set_status(Channel_Status status_) { status = status_; }

    // operators for handlers
#define FUNC_(x) void set_##x##_handler(Callback_t && x##_handler_) { x##_handler = std::move(x##_handler_); }
    PER(FUNC_)
#undef FUNC_

    void handle_events(Timer_Stamp_t);

private:
    // detail implements of handle_events()
#define FUNC_(x) void handle_##x() { if(x##_handler) x##_handler(); }
    PER(FUNC_)
#undef FUNC_

#undef PER
};

} // namespace webserver::net
} // namespace webserver