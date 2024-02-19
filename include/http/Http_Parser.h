#pragma once

#include <http/http_parser.h>

int on_message_begin(http_parser*);

int on_url(http_parser*, const char *at, size_t length);

int on_header_field(http_parser*, const char *at, size_t length);

int on_header_value(http_parser*, const char *at, size_t length);

int on_headers_complete(http_parser*);

int on_body(http_parser*, const char *at, size_t length);

int on_message_complete(http_parser*);