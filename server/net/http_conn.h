#pragma once
#include <memory>
#include <server/net/epoll/epoll_file_handler.h>
#include <server/net/epoll/epoll_loop.h>
#include <server/net/http/http_parser.h>
#include <server/net/http/uri.h>
#include <server/net/socket.h>

namespace server {
namespace net {

struct EpollLoop;

/**
 * Pimpl. The implement is in http_conn.cpp file.
 */
struct ParserImpl {
  http_parser_settings mSetting;
};

/**
 * Epoll file handler for client.
 */
struct ClientFileHandler : EpollFileHandler {
  void handleEvent();
};

/**
 * Client socket fd.
 */
struct HTTPConn : public std::enable_shared_from_this<HTTPConn> {
  explicit HTTPConn(EpollLoop *loop) : mLoop(loop) {}

  ~HTTPConn() = default;

  EpollLoop *mLoop;
  Socket mSock;
  std::unique_ptr<EpollFileHandler> mHandler;

  static ParserImpl mParser;
};
} // namespace net
} // namespace server
