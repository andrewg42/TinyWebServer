#pragma once

#include <unistd.h>
#include <server/config.h>
#include <server/net/acceptor.h>
#include <server/net/http_conn.h>
#include <server/timer/timer_queue.h>
#include <server/utils/noncopyable.h>
#include <sys/epoll.h>
#include <unordered_map>
#include <vector>

namespace webserver {
namespace net {

class Channel;

// RAII encapsulation for epoll
struct Event_Loop {
  // ref:
  // https://github.com/an-tao/trantor/blob/master/trantor/net/inner/poller/EpollPoller.h
public:
  explicit Event_Loop(int port);
  Event_Loop(Event_Loop &&) = delete;

  ~Event_Loop() {
    ::close(ep_fd);
  }

  void loop(
    std::optional<std::chrono::system_clock::duration> timeout = std::nullopt);
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

  bool is_running = false;
  int ep_fd = ::epoll_create1(EPOLL_CLOEXEC);
  std::unique_ptr<Acceptor> p_acceptor;
  std::unique_ptr<timer::Timer_Queue> p_tq;
  std::vector<struct epoll_event>
    events_list; // avoid duplicate allocation of memory
  std::vector<Channel *> activate_channels;
  std::unordered_map<int, std::shared_ptr<Http_Conn>>
    conn_mp; // fd -> http connection
};

} // namespace net
} // namespace webserver
