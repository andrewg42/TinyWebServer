#pragma once

#include <unistd.h>
#include <server/config.h>
#include <sys/epoll.h>
#include <vector>
#include <chrono>
#include <optional>

namespace webserver {
namespace net {

// RAII for epoll
struct EpollLoop {
public:
  EpollLoop(std::size_t buffer_sz) : mEventBuf(buffer_sz) {}

  EpollLoop &operator=(EpollLoop &&) = delete;

  ~EpollLoop() {
    ::close(mEpoll);
  }

  bool loop(
    std::optional<std::chrono::system_clock::duration> timeout = std::nullopt);

  void addListener();
  void removeListener(int fileno);

private:
  bool hasEvent() const noexcept {
    return mCount != 0;
  }

  int mEpoll = ::epoll_create1(EPOLL_CLOEXEC);
  std::size_t mCount = 0;
  std::vector<struct epoll_event> mEventBuf;
};

} // namespace net
} // namespace webserver
