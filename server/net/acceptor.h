#pragma once

#include <server/config.h>
#include <server/net/epoll_details/epoll_file_handler.h>
#include <server/net/socket.h>
#include <server/utils/noncopyable.h>
#include <sys/epoll.h>

namespace server {
namespace net {

struct Event_Loop;
static constexpr uint32_t defaultListenerEvent = EPOLLIN;

/**
 * Listener is a Socket
 */
struct [[nodiscard]] Listener : Socket {
  using Socket::Socket;
};

/**
 * server socket fd. only support:
 *    1. listen socket connections
 *    2. accept new connection (Http_Conn) on a socket
 */
struct Acceptor {
  explicit Acceptor(EpollLoop *loop) : mLoop(loop) {}

  Acceptor(Acceptor &&) = delete;

  EpollFileHandler *handler() {
    return &mHandler;
  }

  void bindAndListen(SocketAddress &addr, int backlog = SOMAXCONN);

  Socket accept(SocketAddress &peerAddr);

  EpollLoop *mLoop;
  Listener mListener;
  EpollFileHandler mHandler;
};

} // namespace net
} // namespace server
