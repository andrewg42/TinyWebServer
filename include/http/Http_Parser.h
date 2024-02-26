#pragma once

#include <http/http_parser.h>


namespace webserver {
namespace http {

int on_message_begin(http_parser* _);

int on_headers_complete(http_parser* _, const char* at, size_t length);

int on_method(http_parser* _);

int on_url(http_parser* _, const char* at, size_t length);

int on_http_version(http_parser* _, const char* at, size_t length);

int on_header_field(http_parser* _, const char* at, size_t length);

int on_header_value(http_parser* _, const char* at, size_t length);

} // namespace webserver::http
} // namesapce webserver