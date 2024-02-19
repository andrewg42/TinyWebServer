#include <http/Http_Parser.h>

#include <cstdio>

int on_message_begin(http_parser*) {
  printf("on_message_begin\n");
  return 0;
}

int on_url(http_parser*, const char *at, size_t length) {
  printf("on_url: %.*s\n", (int)length, at);
  return 0;
}

int on_header_field(http_parser*, const char *at, size_t length) {
  printf("on_header_field: %.*s\n", (int)length, at);
  return 0;
}

int on_header_value(http_parser*, const char *at, size_t length) {
  printf("on_header_value: %.*s\n", (int)length, at);
  return 0;
}

int on_headers_complete(http_parser*) {
  printf("on_headers_complete\n");
  return 0;
}

int on_body(http_parser*, const char *at, size_t length) {
  printf("on_body: %.*s\n", (int)length, at);
  return 0;
}

int on_message_complete(http_parser*) {
  printf("on_message_complete\n");
  return 0;
}