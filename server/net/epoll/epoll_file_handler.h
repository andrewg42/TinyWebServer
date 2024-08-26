#pragma once
#include <unistd.h>
#include <server/net/epoll/epoll_loop.h>
#include <sys/epoll.h>

namespace server {
namespace net {

using EpollEventMask = std::uint32_t;

struct EpollFileHandler {
  // TODO
  explicit EpollFileHandler(EpollLoop *loop) : mLoop(loop) {}

  EpollFileHandler &operator=(EpollFileHandler &&) = delete;

  ~EpollFileHandler() {
    mLoop->removeListener(mFileno);
  }

  virtual void handleEvent() = 0;

  EpollLoop *mLoop;
  int mFileno; // do not hold file, just provide the operations
  EpollEventMask mEvents;
  EpollEventMask mRetEvents;
  int mCtlCode = EPOLL_CTL_ADD;
};

} // namespace net
} // namespace server
