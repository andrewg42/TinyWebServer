#pragma once

#include <server/config.h>
#include <server/utils/noncopyable.h>
#include <server/timer/timer_queue.h>
#include <server/net/http_conn.h>
#include <server/net/acceptor.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <unordered_map>
#include <vector>

namespace webserver {
namespace net {

class Channel;

// RAII encapsulation for epoll
class Event_Loop: public utils::Noncopyable {
// ref: https://github.com/an-tao/trantor/blob/master/trantor/net/inner/poller/EpollPoller.h
private:
    bool is_running;
    int ep_fd;

    std::unique_ptr<Acceptor> p_acceptor;
    std::unique_ptr<timer::Timer_Queue> p_tq;

    std::vector<struct epoll_event> events_list; // avoid duplicate allocation of memory
    std::vector<Channel*> activate_channels;
    std::unordered_map<int, std::shared_ptr<Http_Conn>> conn_mp; // TODO: use absl::flat_hash_map


public:
    // ctor
    explicit Event_Loop(int port);

    // dtor
    ~Event_Loop();

    void loop();

    void add_clnt(std::shared_ptr<Http_Conn> &p_conn);

    void remove_clnt(std::shared_ptr<Http_Conn> &p_conn);

    // update channel in epoll loop by channel::revent
    void mod_channel(Channel *p_chan);

    // remove channel from epoll loop
    void del_channel(Channel *p_chan);

private:
    // call epoll_wait() and get 
    Timer_Stamp_t poll();

    void fill_active_channels(int event_num);
    
};

} // namespace webserver::net
} // namespace webserver