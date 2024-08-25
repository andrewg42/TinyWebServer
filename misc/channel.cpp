#include <server/config.h>
#include <server/net/channel.h>
#include <sys/epoll.h>

namespace server {
namespace net {

void Channel::handleEvents(Timer_Stamp_t now) {
  mIsHandling = true;

  if ((mRevent & EPOLLHUP) && !(mRevent & EPOLLIN)) { // TCP closed
    handle_close();
  }

  if (mRevent & EPOLLERR) { // error
    handle_error();
  }

  if (mRevent & (EPOLLIN | EPOLLPRI | EPOLLRDHUP)) { // read
    handle_read();
  }

  if (mRevent & EPOLLOUT) { // write
    handle_write();
  }

  mRevent = 0;
  mIsHandling = false;
}

} // namespace net
} // namespace server
