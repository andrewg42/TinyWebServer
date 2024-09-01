#pragma once
#include <unistd.h>
#include <chrono>
#include <optional>
#include <sys/epoll.h>
#include <vector>

namespace server {
namespace net {

struct EpollFileHandler;

struct EpollLoop {
  EpollLoop() : mEventList(64) {}

  EpollLoop &operator=(EpollLoop &&) = delete;

  ~EpollLoop() {
    ::close(mEpoll);
  }

  // for acceptor
  bool addListener(EpollFileHandler *file_handler, int ctl);
  void removeListener(int fileno);
  // for event loop
  bool run(
    std::optional<std::chrono::system_clock::duration> timeout = std::nullopt);

private:
  bool hasEvent() const noexcept {
    return 0 != mCount;
  }

  int mEpoll = ::epoll_create1(EPOLL_CLOEXEC);
  int mCount{};
  std::vector<struct epoll_event> mEventList;
};

} // namespace net
} // namespace server
