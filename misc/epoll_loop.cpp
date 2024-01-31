#include "server/utils/error_handle.h"
#include <server/net/epoll_loop.h>
#include <sys/epoll.h>

namespace webserver {
namespace net {

bool EpollLoop::loop(
  std::optional<std::chrono::system_clock::duration> timeout) {
  if (0 == mCount) {
    return false;
  }

  int timeoutInMs = -1;
  if (timeout) {
    timeoutInMs =
      std::chrono::duration_cast<std::chrono::milliseconds>(*timeout).count();
  }
  int rc = utils::checkError(epoll_wait(
    mEpoll, mEventBuf.data(), static_cast<int>(mEventBuf.size()), timeoutInMs));

  // TODO
}

void EpollLoop::addListener() {}

void EpollLoop::removeListener(int fileno) {}

} // namespace net
} // namespace webserver
