#pragma once

#include <server/net/http/http_parser.h>

namespace server {
namespace net {

int on_message_begin(http_parser *_);

int on_headers_complete(http_parser *_, char const *at, size_t length);

int on_method(http_parser *_);

int on_url(http_parser *_, char const *at, size_t length);

int on_http_version(http_parser *_, char const *at, size_t length);

int on_header_field(http_parser *_, char const *at, size_t length);

int on_header_value(http_parser *_, char const *at, size_t length);

} // namespace net
} // namespace server
