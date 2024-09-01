#include "server/net/epoll/epoll_loop.h"
#include "server/net/http_conn.h"
#include <server/net/http_server.h>
#include <server/net/socket.h>

namespace server {
namespace net {

std::unique_ptr<HTTPConn> HTTPServer::handleNewConn(Socket sock) {
  return std::make_unique<HTTPConn>(&mEpoll, std::move(sock));
}

void HTTPServer::run() {
  // build acceptor
  struct sockaddr_in addr = {
    .sin_family = AF_INET,
    .sin_port = htons(mPort),
    .sin_addr =
      {
        .s_addr = htonl(INADDR_LOOPBACK),
      },
  };
  Acceptor acceptor{SocketAddress{(struct sockaddr *)(&addr), sizeof(addr)}};

  // run main loop
  // TODO
  while (true) {
    if (auto income = acceptor.accept()) [[likely]] {
      mEpoll.addListener(EpollFileHandler *file_handler, int ctl)handleNewConn(std::move(income));
    }
  }
}

} // namespace net
} // namespace server
