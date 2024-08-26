#pragma once

#include "server/net/epoll_details/epoll_loop.h"
#include <memory>
#include <server/config.h>
#include <server/net/epoll_details/epoll_file_handler.h>
#include <server/net/http_details/http_parser.h>
#include <server/net/socket.h>
#include <server/utils/buffer.h>
#include <server/utils/noncopyable.h>
#include <sys/epoll.h>
#include <sys/stat.h>
#include <sys/uio.h>

namespace server {
namespace net {

struct Event_Loop;

/**
 * @brief Client socket.
 *      Notice that this class inherits from the Socket class.
 */
struct HTTPConn : public std::enable_shared_from_this<HTTPConn> {
  explicit HTTPConn(EpollLoop *loop, int fd_);

  ~HTTPConn() = default;

/*
  void do_request();

  void unmap();
  // append message to response
  bool append_response(std::string_view str);

  bool add_headers(std::size_t content_len);
  bool add_content_length(std::size_t content_len);
  bool add_content_type();
  bool add_linger();
  bool add_blank_line();

  // generate response based on http_parser
  bool gen_response();

  void read_handler();

  void write_handler();

  void close_handler();

  void error_handler();

  std::unique_ptr<Channel> p_chan;
  utils::Buffer<READ_BUFFER_SZ> read_buffer;
  utils::Buffer<WRITE_BUFFER_SZ> write_buffer;
  struct stat file_stat;
  std::string filename;
  char *file_addr;
  // for write file
  struct iovec iv[2];
  int iv_cnt;
  */
  
  EpollLoop *mLoop;
  EpollFileHandler mHandler;

  // for http
  struct ParserImpl;
  std::unique_ptr<ParserImpl> mParser;
  static http_parser_settings mSetting;

};

} // namespace net
} // namespace server
