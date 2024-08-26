#include <chrono>
#include <optional>
#include <server/net/epoll/epoll_file_handler.h>
#include <server/net/epoll/epoll_loop.h>
#include <server/utils/error_handling.h>

namespace server {
namespace net {

bool EpollLoop::addListener(EpollFileHandler &file_handler, int ctl) {
  struct epoll_event event;
  // TODO
  event.events = file_handler.mEvents;
  event.data.ptr = &file_handler;
  utils::checkError(
    epoll_ctl(mEpoll, EPOLL_CTL_ADD, file_handler.mFileno, &event));
}

void EpollLoop::removeListener(int fileno) {
  utils::checkError(epoll_ctl(mEpoll, EPOLL_CTL_DEL, fileno, NULL));
  --mCount;
}

bool EpollLoop::run(
  std::optional<std::chrono::system_clock::duration> timeout) {}

} // namespace net
} // namespace server
