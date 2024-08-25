#pragma once

#include <server/net/http_details/http_parser.h>

namespace server {
namespace net {
namespace http {

int on_message_begin(http_parser *_);

int on_headers_complete(http_parser *_, char const *at, size_t length);

int on_method(http_parser *_);

int on_url(http_parser *_, char const *at, size_t length);

int on_http_version(http_parser *_, char const *at, size_t length);

int on_header_field(http_parser *_, char const *at, size_t length);

int on_header_value(http_parser *_, char const *at, size_t length);

} // namespace http
} // namespace net
} // namespace server
