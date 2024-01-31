#include <arpa/inet.h>
#include <netinet/in.h>
#include <server/log/log.h>
#include <server/net/socket.h>
#include <stdexcept>
#include <sys/socket.h>
#include <utility>

namespace webserver {
namespace net {

//static constexpr int BACKLOG = 4096;

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
