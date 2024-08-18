#pragma once

#include <unistd.h>
#include "server/net/file_handling.h"
#include <arpa/inet.h>
#include <server/log/log.h>
#include <server/net/file_handling.h>
#include <server/utils/noncopyable.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>

namespace webserver {
namespace net {

/*
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
};*/

struct SocketAddress {
  // only support IPv4 now
  SocketAddress() = default;

  explicit SocketAddress(struct sockaddr const *addr, socklen_t addrLen,
                         sa_family_t family, int sockType, int protocol)
      : mSockType(sockType),
        mProtocol(protocol) {
    std::memcpy(&mAddr, addr, addrLen);
    mAddr.ss_family = family;
    mAddrLen = addrLen;
  }

  sa_family_t family() const noexcept {
    return mAddr.ss_family;
  }

  int socktype() const noexcept {
    return mSockType;
  }

  int protocol() const noexcept {
    return mProtocol;
  }

  std::string host() const;
  int port() const;
  void trySetPort(int port);

  auto repr() const {
    return host() + ':' + std::to_string(port());
  }

private:
  struct sockaddr_storage mAddr;
  socklen_t mAddrLen;
  int mSockType;
  int mProtocol;
};

struct [[nodiscard]] SocketHandler : FileHandler {
  using FileHandler::FileHandler;
};

inline static SocketHandler createSocket(int family, int type, int protocol);
inline static SocketHandler socketConnect();

} // namespace net
} // namespace webserver
