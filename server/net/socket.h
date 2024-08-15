#pragma once

#include <unistd.h>
#include <arpa/inet.h>
#include <server/log/log.h>
#include <server/utils/noncopyable.h>
#include <sys/socket.h>
#include <sys/types.h>

namespace webserver {
namespace net {

// RAII encapsulation for TCP server socket
class Socket : public utils::Noncopyable {
public:
  // ctor
  explicit Socket(int fd) : sock_fd(fd) {}

  // dtor
  ~Socket() {
    close();
  }

  // move ctor
  Socket(Socket &&rhs) noexcept;

  // move assign
  Socket &operator=(Socket &&rhs) noexcept;

  // close fd
  void close();

  // enable KEEPALIVE
  void set_keep_alive();

  // get sock_fd
  int get_fd() const {
    return sock_fd;
  }

private:
  // check if fd is closed
  bool is_closed() const {
    return -1 == sock_fd;
  }

protected:
  int sock_fd;
};

} // namespace net
} // namespace webserver
