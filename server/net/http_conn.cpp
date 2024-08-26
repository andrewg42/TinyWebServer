#include <server/net/http_conn.h>
#include <server/net/http_details/http_parser.h>

namespace server {
namespace net {

struct EpollLoop;

struct HTTPConn::ParserImpl {
    static http_parser_settings mSetting;
};

HTTPConn(EpollLoop *loop) : mLoop(loop) {}

} // namespace net
} // namespace server