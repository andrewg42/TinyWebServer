#pragma once
#include <memory>
#include <server/net/epoll_details/epoll_file_handler.h>
#include <server/net/epoll_details/epoll_loop.h>

namespace server {
namespace net {

struct EpollLoop;

struct ParserImpl {

};

struct HTTPConn : public std::enable_shared_from_this<HTTPConn> {

  explicit HTTPConn(EpollLoop *loop);

  EpollLoop *mLoop;
  EpollFileHandler mHandler;

  static ParserImpl mParser;
};
} // namespace net
} // namespace server
