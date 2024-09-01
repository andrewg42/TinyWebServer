#pragma once
#include <unistd.h>
#include <arpa/inet.h>
#include <server/log/log.h>
#include <server/utils/file_handler.h>
#include <server/utils/noncopyable.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>

namespace server {
namespace net {

/**
 * Encapsulate the address operations of socket
 * i.e. struct sockaddr.
 */
struct SocketAddress {
  SocketAddress() = default;

  explicit SocketAddress(struct sockaddr const *addr, socklen_t addrLen,
                         sa_family_t family = AF_INET,
                         int sockType = SOCK_STREAM, int protocol = IPPROTO_IP)
      : mSockType(sockType),
        mProtocol(protocol) {
    ::memcpy(&mAddr, addr, addrLen);
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

  // address family, address value(ip and port), other data and padding
  struct sockaddr_storage mAddr;
  socklen_t mAddrLen;
  // type of socket. may be SOCK_STREAM, SOCK_DGRAM, ...
  int mSockType;
  // protocol. may be IPPROTO_IP, ...
  int mProtocol;
};

/**
 * Socket is a file
 */
struct [[nodiscard]] Socket : utils::FileHandler {
  using utils::FileHandler::FileHandler;
};

/**
 * The socket may be closed.
 * So do not use member function.
 */
// getsockname
extern SocketAddress getSockAddr(Socket &sock);
// getpeername
extern SocketAddress getSockPeerAddr(Socket &sock);

// for Acceptor and Http_Conn
extern Socket createSocket(int family, int sockType, int protocol);

template <class T>
extern int socketSetOption(Socket &sock, int level, int opt,
                                  T const &optVal) {
  return ::setsockopt(sock.fileno(), level, opt, &optVal, sizeof(optVal));
}

} // namespace net
} // namespace server
