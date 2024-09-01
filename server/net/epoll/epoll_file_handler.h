#pragma once
#include <unistd.h>
#include <cstdint>
#include <server/net/epoll/epoll_loop.h>
#include <sys/epoll.h>

namespace server {
namespace net {

struct EpollLoop;
using EpollEventMask = std::uint32_t;
static EpollEventMask const kNoneEvent = 0;
static EpollEventMask const kReadEvent = EPOLLIN | EPOLLPRI;
static EpollEventMask const kWriteEvent = EPOLLOUT;

struct EpollFileHandler {
  // assert fileno != -1
  explicit EpollFileHandler(EpollLoop *loop, int fileno, EpollEventMask events)
      : mLoop(loop),
        mFileno(fileno),
        mEvents(events) {
    mLoop->addListener(this, mCtlCode);
  }

  EpollFileHandler &operator=(EpollFileHandler &&) = delete;

  virtual ~EpollFileHandler() {
    mLoop->removeListener(mFileno);
  }

  virtual void handleEvent() = 0;

  EpollLoop *mLoop;
  int mFileno; // do not hold file, just a weak reference
  EpollEventMask mEvents;
  EpollEventMask mRetEvents;
  int mCtlCode = EPOLL_CTL_ADD;
};

} // namespace net
} // namespace server
