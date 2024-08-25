#pragma once
#include <unistd.h>
#include <server/net/epoll_details/epoll_loop.h>
#include <sys/epoll.h>

namespace server {
namespace net {

using EpollEventMask = std::uint32_t;

struct EpollFileHandler {
  EpollFileHandler &operator=(EpollFileHandler &&) = delete;

  ~EpollFileHandler() {
    mLoop->removeListener(mFileno);
  }

  EpollLoop *mLoop;
  int mFileno; // do not hold file, just provide the operations
  EpollEventMask mEvents;
  EpollEventMask mRetEvents;
  int mCtlCode = EPOLL_CTL_ADD;
};

} // namespace net
} // namespace server
