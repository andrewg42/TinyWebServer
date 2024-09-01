#pragma once
#include "server/net/socket.h"
#include <server/log/log.h>
#include <server/net/acceptor.h>
#include <server/net/epoll/epoll_loop.h>
#include <server/net/http_conn.h>

namespace server {

using namespace net;

struct WebServer {
public:
  explicit WebServer(int port) : mPort(port) {}

  void loop() {
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

    // build epolls

    // run main loop
    while (true) {
      if (auto income = acceptor.accept()) {
        
      }
    }
  }

private:
  int mPort;
};

} // namespace server
