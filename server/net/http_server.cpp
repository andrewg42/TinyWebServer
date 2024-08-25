#include <server/net/http_server.h>
#include <map>

namespace server {
namespace net {

struct HTTPServer::Impl {
    
};

HTTPServer::HTTPServer() : mImpl(std::make_unique<Impl>()) {}

} // namespace net
} // namespace server
