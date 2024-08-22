#pragma once

#include <memory>
#include <server/config.h>
#include <server/net/channel.h>
#include <server/net/http_parser.h>
#include <server/net/socket.h>
#include <server/utils/buffer.h>
#include <server/utils/noncopyable.h>
#include <sys/epoll.h>
#include <sys/stat.h>
#include <sys/uio.h>

namespace webserver {
namespace net {

class Event_Loop;
class Channel;

/**
 * @brief Client socket.
 *      Notice that this class inherits from the Socket class.
 *
 */
class Http_Conn : public Socket,
                  public std::enable_shared_from_this<Http_Conn> {
public:
  /**
   * @brief Construct a new Http_Conn object
   *
   * @param p_loop_ : For p_loop
   * @param fd_ : File descriptor of client socket, for p_sock
   */
  explicit Http_Conn(Event_Loop *p_loop_, int fd_);

  /**
   * @brief Destroy the Http_Conn object
   *
   */
  ~Http_Conn() = default;

  /**
   * @brief Initialization of p_chan
   *
   */
  void init_chan();

  /**
   * @brief Get the pointer p_chan
   *
   * @return Channel*
   */
  Channel *get_chan() {
    return p_chan.get();
  }

private:
  void do_request();

  void unmap();
  /**
   * @brief append message to response
   *
   * @param str : message
   * @return true : append successfully
   * @return false : have some error
   */
  bool append_response(std::string_view str);

  bool add_headers(std::size_t content_len);
  bool add_content_length(std::size_t content_len);
  bool add_content_type();
  bool add_linger();
  bool add_blank_line();

  /**
   * @brief generate response based on http_parser
   *
   * @return true : generate response successfully
   * @return false : have error
   */
  bool gen_response();

  /**
   * @brief
   *
   */
  void read_handler();

  /**
   * @brief
   *
   */
  void write_handler();

  /**
   * @brief
   *
   */
  void close_handler();

  /**
   * @brief
   *
   */
  void error_handler();

private:
  Event_Loop *mLoop; // Pointer to thr loop (for callback)
  static http_parser_settings settings;
  http_parser parser;

  std::unique_ptr<Channel> p_chan;
  utils::Buffer<READ_BUFFER_SZ> read_buffer;
  utils::Buffer<WRITE_BUFFER_SZ> write_buffer;
  struct stat file_stat;
  std::string filename;
  char *file_addr;
  // for write file
  struct iovec iv[2];
  int iv_cnt;
};

} // namespace net
} // namespace webserver
