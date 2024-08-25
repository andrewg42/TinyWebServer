#include <arpa/inet.h>
#include <chrono>
#include <netinet/in.h>
#include <server/log/log.h>
#include <server/net/socket.h>
#include <server/utils/error_handling.h>
#include <stdexcept>
#include <sys/socket.h>

namespace server {
namespace net {

// static constexpr int BACKLOG = 4096;

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

SocketAddress getSockAddr(Socket &sock) {
  SocketAddress sa;
  sa.mAddrLen = sizeof(sa.mAddr);
  utils::checkError(
    ::getsockname(sock.fileno(), reinterpret_cast<struct sockaddr *>(&sa.mAddr),
                  &sa.mAddrLen));
  return sa;
}

SocketAddress getSockPeerAddr(Socket &sock) {
  SocketAddress sa;
  sa.mAddrLen = sizeof(sa.mAddr);
  utils::checkError(
    ::getpeername(sock.fileno(), reinterpret_cast<struct sockaddr *>(&sa.mAddr),
                  &sa.mAddrLen));
  return sa;
}

Socket createSocket(int family, int sockType, int protocol) {
  int fd = ::socket(family, sockType, protocol);
  return Socket(fd);
}

} // namespace net
} // namespace server
