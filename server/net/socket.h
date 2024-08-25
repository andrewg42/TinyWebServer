#pragma once

#include <unistd.h>
#include <arpa/inet.h>
#include <chrono>
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

  struct sockaddr_storage mAddr; // address value and family
  socklen_t mAddrLen;
  int mSockType; // type of socket. may be SOCK_STREAM, SOCK_DGRAM, ...
  int mProtocol; // protocol. may be IPPROTO_IP, ...
};

/**
 * Socket is a FileHandler.
 */
struct [[nodiscard]] Socket : utils::FileHandler {
  using utils::FileHandler::FileHandler;
};

/**
 * The socket may be closed.
 * So do not use member function.
 */
// getsockname
static inline SocketAddress getSockAddr(Socket &sock);
// getpeername
static inline SocketAddress getSockPeerAddr(Socket &sock);

// for Acceptor and Http_Conn
static inline Socket createSocket(int family, int sockType, int protocol);

template <class T>
static inline int socketSetOption(Socket &sock, int level, int opt,
                                  T const &optVal) {
  return ::setsockopt(sock.fileno(), level, opt, &optVal, sizeof(optVal));
}

} // namespace net
} // namespace server
