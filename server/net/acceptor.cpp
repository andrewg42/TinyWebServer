#include <cassert>
#include <server/config.h>
#include <server/log/log.h>
#include <server/net/acceptor.h>
#include <server/net/socket.h>
#include <server/utils/error_handling.h>

namespace server {
namespace net {

static void bindAndListen(int listenerFileno, SocketAddress &addr,
                          int backlog) {
  utils::checkError(::bind(
    listenerFileno, reinterpret_cast<struct sockaddr const *>(&addr.mAddr),
    addr.mAddrLen));
  utils::checkError(listen(listenerFileno, backlog));
}

Acceptor::Acceptor(SocketAddress addr, int backlog) {
  Socket sock = createSocket(addr.family(), addr.socktype(), addr.protocol());
  socketSetOption(sock, SOL_SOCKET, SO_REUSEADDR, 1);
  socketSetOption(sock, SOL_SOCKET, SO_REUSEPORT, 1);
  mListener = Listener(sock.releaseFile());
  assert(static_cast<bool>(mListener));

  bindAndListen(mListener.fileno(), addr, backlog);
}

Socket Acceptor::accept() {
  int fd =
    utils::checkError(::accept4(mListener.fileno(), nullptr, nullptr, 0));
  return Socket(fd);
}

Socket Acceptor::accept(SocketAddress &peerAddr) {
  int fd = utils::checkError(::accept4(
    mListener.fileno(), reinterpret_cast<struct sockaddr *>(&peerAddr.mAddr),
    &peerAddr.mAddrLen, 0)); // flags = SOCK_NONBLOCK | SOCK_CLOEXEC
  return Socket(fd);
}

} // namespace net
} // namespace server
