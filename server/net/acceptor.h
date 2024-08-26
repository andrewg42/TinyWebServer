#pragma once

#include <server/config.h>
#include <server/net/epoll/epoll_file_handler.h>
#include <server/net/socket.h>
#include <server/utils/noncopyable.h>
#include <sys/epoll.h>

namespace server {
namespace net {

struct Event_Loop;
static constexpr uint32_t defaultListenerEvent = EPOLLIN;

/**
 * Listener is also a Socket.
 */
struct [[nodiscard]] Listener : Socket {
  using Socket::Socket;
};

/**
 * Epoll file handler for listener
 */
struct ListenerFileHandler : EpollFileHandler {
  void handleEvent();
};

/**
 * Server socket fd. only support:
 *    1. listen socket connections
 *    2. accept new connection (Http_Conn) on a socket
 */
struct Acceptor {
  explicit Acceptor(EpollLoop *loop) : mLoop(loop) {}

  Acceptor(Acceptor &&) = delete;

  void bindAndListen(SocketAddress &addr, int backlog = SOMAXCONN);

  Socket accept(SocketAddress &peerAddr);

  EpollLoop *mLoop;
  Listener mListener;
  std::unique_ptr<EpollFileHandler> mHandler;
};

} // namespace net
} // namespace server
