#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <server/config.h>
#include <server/log/log.h>
#include <server/net/acceptor.h>
#include <server/net/channel.h>
#include <server/net/event_loop.h>
#include <sys/epoll.h>

namespace server {
namespace net {

static constexpr int EPOLL_TIMEOUT = 10000;

Event_Loop::Event_Loop(int port)
    : p_acceptor(std::make_unique<Acceptor>(this, port)),
      p_tq(std::make_unique<timer::Timer_Queue>()),
      events_list(EVENT_LIST_SZ) {
  if (-1 == ep_fd) {
    LOG_ERROR("epoll_create()");
  }
  mod_channel(p_acceptor->get_chan());
}

void Event_Loop::loop(std::optional<std::chrono::system_clock::duration> timeout) {
  is_running = true;

  while (is_running) {
    auto now = poll();

    // TODO: dispatch into threadpool
    for (Channel *p_chan: activate_channels) {
      if (!p_chan->is_handling()) {
        p_chan->handle_events(now);
      }
    }
    activate_channels.clear();

    // handle expired timer, NO I/O
    auto timer_list = p_tq->tick(now);
    for (std::size_t i{}; i < timer_list.size(); i++) {
      timer_list[i]->callback();
    }
  }
}

void Event_Loop::add_clnt(std::shared_ptr<Http_Conn> &p_conn) {
  int const fd = p_conn->get_fd();
  LOG_DEBUG(__func__, ": , fd = {}", fd);

  if (conn_mp.find(fd) != conn_mp.end()) {
    LOG_ERROR(__func__, ": , fd = {}", fd);
    return;
  }

  conn_mp.emplace(std::pair(fd, p_conn));
  LOG_DEBUG("conn_mp size = {}", conn_mp.size());
  mod_channel(p_conn->get_chan());
}

void Event_Loop::remove_clnt(std::shared_ptr<Http_Conn> &p_conn) {
  del_channel(p_conn->get_chan());

  int const fd = p_conn->get_fd();
  if (conn_mp.find(fd) != conn_mp.end()) {
    conn_mp.erase(fd);
  }
}

void Event_Loop::mod_channel(Channel *p_chan) {
  struct epoll_event ev;
  bzero(&ev, sizeof ev);
  ev.events = p_chan->get_event();
  ev.data.ptr = p_chan;

  Channel_Status const cur_status = p_chan->get_status();
  if (cur_status != Channel_Status::added) {
    epoll_ctl(ep_fd, EPOLL_CTL_ADD, p_chan->get_fd(), &ev);
    p_chan->set_status(Channel_Status::added);
  } else {
    epoll_ctl(ep_fd, EPOLL_CTL_MOD, p_chan->get_fd(), &ev);
  }
}

void Event_Loop::del_channel(Channel *p_chan) {
  // remove from epoll
  epoll_ctl(ep_fd, EPOLL_CTL_DEL, p_chan->get_fd(), NULL);

  // remove channel
  p_chan->set_status(Channel_Status::removed);
}

void Event_Loop::fill_active_channels(int event_num) {
  for (int i{}; i < event_num; i++) {
    Channel *chan = reinterpret_cast<Channel *>(events_list[i].data.ptr);
    chan->set_revent(events_list[i].events);
    activate_channels.push_back(chan);
  }
}

Timer_Stamp_t Event_Loop::poll() {
  int eve_num =
    ::epoll_wait(ep_fd, events_list.data(),
                 static_cast<int>(events_list.size()), EPOLL_TIMEOUT);
  Timer_Stamp_t now = std::chrono::steady_clock::now();

  int saved_errno = errno;
  if (0 < eve_num) {
    LOG_DEBUG("{} events happened", eve_num);
    fill_active_channels(eve_num);
    if (static_cast<std::size_t>(eve_num) == events_list.size()) {
      events_list.resize(2 * events_list.size());
    }
  } else if (0 == eve_num) {
    LOG_DEBUG("nothing happened");
  } else {
    if (saved_errno != EINTR) {
      errno = saved_errno;
      LOG_ERROR("Reactor::poll()");
    }
  }

  return now;
}


} // namespace net
} // namespace server
