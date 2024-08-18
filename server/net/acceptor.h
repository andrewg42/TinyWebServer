#pragma once

#include <server/config.h>
#include <server/net/channel.h>
#include <server/net/socket.h>
#include <server/utils/noncopyable.h>
#include <sys/epoll.h>

namespace webserver {
namespace net {

struct Event_Loop;

struct [[nodiscard]] SocketListener : SocketHandler {
  using SocketHandler::SocketHandler;
};

// server socket fd: only support:
// 1. listen socket connections
// 2. accept new connection (Http_Conn) on a socket
struct Acceptor: SocketListener {
public:
  // ctor
  explicit Acceptor(Event_Loop *p_loop_, int port);

  Channel *chan() {
    return &mChann;
  }

private:
  void bindAndListen(int port);

  void read_handler();

  // listen for socket connections and accept new connection on socket
  int accept(sockaddr_in *p_clnt_addr);

private:
  Event_Loop *mLoop;
  // frequently used and will not be easily closed
  // directly use member variables
  Channel mChann;
};

} // namespace net
} // namespace webserver
