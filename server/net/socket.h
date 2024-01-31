#pragma once

#include <unistd.h>
#include <server/utils/file_handler.h>
#include <arpa/inet.h>
#include <server/log/log.h>
#include <server/utils/noncopyable.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>

namespace webserver {
namespace net {

/**
 * Encapsulate the address operations of socket
 * i.e. struct sockaddr
 */
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

/**
 * Socket is a kind of file.
 */
struct [[nodiscard]] Socket : utils::FileHandler {
  using utils::FileHandler::FileHandler;
};

/**
 * The socket may be closed.
 * So do not use member function.
 */
inline static Socket createSocket(int family, int type, int protocol);
//inline static Socket socketConnect();

} // namespace net
} // namespace webserver
