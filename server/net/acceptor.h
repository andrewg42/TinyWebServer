#pragma once
#include <server/config.h>
#include <server/net/socket.h>
#include <sys/epoll.h>
#include <sys/socket.h>

namespace server {
namespace net {

struct EpollLoop;
static constexpr uint32_t defaultListenerEvent = EPOLLIN;

/**
 * Listener is a Socket.
 */
struct [[nodiscard]] Listener : Socket {
  using Socket::Socket;
};

/**
 * Server socket fd. only support:
 *    1. listen socket connections
 *    2. accept new connection (Http_Conn) on a socket
 */
struct Acceptor {
  // create listener, then bind() and listen()
  explicit Acceptor(SocketAddress addr, int backlog = SOMAXCONN);

  Acceptor operator=(Acceptor &&) = delete;

  // ::accept4()
  // return a socket, then the server can do some operator on it.
  Socket accept();
  Socket accept(SocketAddress &peerAddr);

private:
  Listener mListener;
};

} // namespace net
} // namespace server
