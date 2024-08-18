#include <arpa/inet.h>
#include <netinet/in.h>
#include <server/log/log.h>
#include <server/net/socket.h>
#include <stdexcept>
#include <sys/socket.h>
#include <utility>

namespace webserver {
namespace net {

static constexpr int BACKLOG = 4096;

/*
Socket::Socket(Socket &&rhs) noexcept {
  sock_fd = rhs.sock_fd;
  rhs.sock_fd = -1;
}

Socket &Socket::operator=(Socket &&rhs) noexcept {
  std::swap(sock_fd, rhs.sock_fd);
  return *this;
}

void Socket::close() {
  LOG_DEBUG("socket = {}, close()", sock_fd);
  if (!is_closed()) {
    if (-1 == ::close(sock_fd)) {
      LOG_ERROR("socket = {}, close()", sock_fd);
    }
  }
}

void Socket::set_keep_alive() {
  LOG_DEBUG("socket = {}, set_keep_alive()", sock_fd);
  uint32_t optval = 1;
  if (0 != ::setsockopt(sock_fd, SOL_SOCKET, SO_KEEPALIVE, &optval,
                        static_cast<socklen_t>(sizeof optval))) {
    LOG_ERROR("socket = {}, set_keep_alive()", sock_fd);
  }
}*/

std::string SocketAddress::host() const {
  if (family() == AF_INET) {
    auto &sin = reinterpret_cast<struct sockaddr_in const &>(mAddr).sin_addr;
    char buf[INET_ADDRSTRLEN]{};
    inet_ntop(AF_INET, &sin, buf, sizeof(buf));
    return buf;
  } else [[unlikely]] {
    throw std::runtime_error("address family not ipv4.");
  }
}

int SocketAddress::port() const {
  if (family() == AF_INET) {
    auto port = reinterpret_cast<struct sockaddr_in const &>(mAddr).sin_port;
    return ntohs(port);
  } else [[unlikely]] {
    throw std::runtime_error("address family not ipv4.");
  }
}

void SocketAddress::trySetPort(int port) {
  if (family() == AF_INET) {
    reinterpret_cast<struct sockaddr_in &>(mAddr).sin_port =
      htons(static_cast<short>(port));
  } else [[unlikely]] {
    throw std::runtime_error("address family not ipv4.");
  }
}

SocketHandler createSocket(int family, int type, int protocol) {
  int fd = ::socket(family, type, protocol);
  return SocketHandler(fd);
}

} // namespace net
} // namespace webserver
