#pragma once
#include <server/net/acceptor.h>
#include <server/net/epoll/epoll_loop.h>
#include <server/net/http_conn.h>
#include <server/net/socket.h>
#include <vector>

namespace server {
namespace net {

struct HTTPServer {
  HTTPServer(int port, int epollNum) : mPort(port), mEpoll{} {}

  HTTPServer(HTTPServer &&) = delete;

  ~HTTPServer() = default;

  void run();

private:
  std::unique_ptr<HTTPConn> handleNewConn(Socket);

  int mPort;
  EpollLoop mEpoll;
};

} // namespace net
} // namespace server
