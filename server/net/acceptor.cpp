#include "server/utils/error_handling.h"
#include <server/config.h>
#include <server/log/log.h>
#include <server/net/acceptor.h>
#include <server/net/socket.h>

namespace server {
namespace net {

void ListenerFileHandler::handleEvent() {
  // TODO
}

void Acceptor::bindAndListen(SocketAddress &addr, int backlog) {
  Socket sock = createSocket(addr.family(), addr.socktype(), addr.protocol());
  socketSetOption(sock, SOL_SOCKET, SO_REUSEADDR, 1);
  socketSetOption(sock, SOL_SOCKET, SO_REUSEPORT, 1);

  mListener = Listener(sock.releaseFile());
  utils::checkError(::bind(
    mListener.fileno(), reinterpret_cast<struct sockaddr const *>(&addr.mAddr),
    addr.mAddrLen));
  utils::checkError(listen(mListener.fileno(), backlog));
}

Socket Acceptor::accept(SocketAddress &peerAddr) {
  int fd = utils::checkError(::accept4(
    mListener.fileno(), reinterpret_cast<struct sockaddr *>(&peerAddr.mAddr),
    &peerAddr.mAddrLen, 0));
  return Socket(fd);
}

/* // TODO
Acceptor::Acceptor(Event_Loop *loop, int port)
    : SocketListener(),
      mLoop(loop),
      Socket(::socket(PF_INET, SOCK_STREAM, 0)),
      chan(mLoop_, get_fd(), default_event) {
  if (-1 == get_fd()) {
    LOG_ERROR("socket()");
  } else {
    bind_and_listen(port);
    chan.set_read_handler(std::bind(&Acceptor::read_handler, this));
  }
}

void Acceptor::bindAndListen(int port) {
  int const servFileno = fileno();

  struct sockaddr_in serv_addr;
  ::memset(&serv_addr, 0, sizeof serv_addr);

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY; //::inet_addr(ip)
  serv_addr.sin_port = ::htons(port);

  if (-1 == ::bind(servFileno, reinterpret_cast<sockaddr *>(&serv_addr),
                   sizeof serv_addr)) {
    LOG_ERROR("bind()");
  } else {
    if (-1 == ::listen(servFileno, SOCK_BACKLOG)) {
      LOG_ERROR("listen()");
    }
  }
}

void Acceptor::read_handler() {
  LOG_DEBUG("Acceptor::read_handler()");

  sockaddr_in clnt_addr;

  int clnt_fd = accept(&clnt_addr);

  if (0 > clnt_fd) {
    LOG_ERROR(__func__);
  } else {
    auto p_conn = std::make_shared<Http_Conn>(mLoop, clnt_fd);
    p_conn->init_chan();
    mLoop->add_clnt(p_conn);
  }
}

int Acceptor::accept(sockaddr_in *p_clnt_addr) {
  socklen_t clnt_addr_sz = sizeof(struct sockaddr_in);
  int clnt_sock = ::accept4(sock_fd, reinterpret_cast<sockaddr *>(p_clnt_addr),
                            &clnt_addr_sz, SOCK_NONBLOCK | SOCK_CLOEXEC);

  if (-1 == clnt_sock) {
    LOG_ERROR("socket = {}, accept()", sock_fd);
  }
  return clnt_sock;
}
*/
} // namespace net
} // namespace server
