#include <server/net/epoll/epoll_file_handler.h>
#include <map>
#include <server/net/http_server.h>

namespace server {
namespace net {

struct HTTPServer::Impl {
  std::map<int, EpollFileHandler> mConnMap;
};

HTTPServer::HTTPServer() : mImpl(std::make_unique<Impl>()) {}

} // namespace net
} // namespace server
