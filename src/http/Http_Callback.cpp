#pragma once

#include <stdio.h>
#include <http/Http_Parser.h>

int on_message_begin(http_parser* _) {
  (void)_;
  printf("\n***MESSAGE BEGIN***\n\n");
  return 0;
}

int on_headers_complete(http_parser* _) {
  (void)_;
  printf("\n***HEADERS COMPLETE***\n\n");
  return 0;
}

int on_message_complete(http_parser* _) {
  (void)_;
  _->rqst.done = true;
  return 0;
}

int on_url(http_parser* _, const char* at, size_t length) {
  (void)_;
  printf("Url: %.*s\n", (int)length, at);
  return 0;
}

int on_header_field(http_parser* _, const char* at, size_t length) {
  (void)_;
  printf("Header field: %.*s\n", (int)length, at);
  return 0;
}

int on_header_value(http_parser* _, const char* at, size_t length) {
  (void)_;
  printf("Header value: %.*s\n", (int)length, at);
  return 0;
}

int on_body(http_parser* _, const char* at, size_t length) {
  (void)_;
  printf("Body: %.*s\n", (int)length, at);
  return 0;
}