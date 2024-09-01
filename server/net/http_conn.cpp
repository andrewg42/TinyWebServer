#include <memory>
#include <server/net/epoll/epoll_file_handler.h>
#include <server/net/http/http_parser.h>
#include <server/net/http_conn.h>

namespace server {
namespace net {

void ClientFileHandler::handleEvent() {
  // TODO
}

std::unique_ptr<EpollFileHandler> createHandler(EpollLoop *loop, int fileno) {
  return std::make_unique<ClientFileHandler>(loop, fileno,
                                             kReadEvent | kWriteEvent);
}

HTTPConn::HTTPConn(EpollLoop *loop, Socket sock)
    : mLoop(loop),
      mSock(sock.releaseFile()),
      mHandler(createHandler(loop, mSock.fileno())) {}

} // namespace net
} // namespace server
