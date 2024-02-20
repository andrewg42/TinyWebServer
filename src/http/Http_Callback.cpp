#include <cstdio>
#include <map>
#include <string_view>
#include "http/http_parser.h"
#include <http/Http_Parser.h>

enum class Http_Header: unsigned char {
    CONNECTION = 0,
};

static std::map<std::string_view, Http_Header> http_header_mp = {
    { "Connection", Http_Header::CONNECTION },
};

int on_message_begin(http_parser* _) {
    (void)_;
    //printf("\n***MESSAGE BEGIN***\n\n");
    return 0;
}

int on_headers_complete(http_parser* _) {
    (void)_;
    //printf("\n***HEADERS COMPLETE***\n\n");
    return 0;
}

int on_message_complete(http_parser* _) {
    (void)_;
    _->rqst.done = true;
    return 0;
}

int on_url(http_parser* _, const char* at, size_t length) {
    (void)_;
    //printf("Url: %.*s\n", (int)length, at);
    _->rqst.url = std::string_view(at, length);
    return 0;
}

int on_header_field(http_parser* _, const char* at, size_t length) {
    (void)_;
    //printf("Header field: %.*s\n", (int)length, at);
    _->rqst.field_at = (char*)at;
    _->rqst.field_len = length;
    _->rqst.update = true;
    return 0;
}

int on_header_value(http_parser* _, const char* at, size_t length) {
    (void)_;
    //printf("Header value: %.*s\n", (int)length, at);
    if(true != _->rqst.update) return 0;

    std::string_view field_view(_->rqst.field_at, _->rqst.field_len);
    auto it = http_header_mp.find(field_view);
    if(http_header_mp.end() == it) return 0;
    Http_Header field_mark = it->second;
    switch (field_mark) {
    case Http_Header::CONNECTION: {
        std::string_view value_view(at, length);
        if(value_view == "keep-alive") {
            _->rqst.connection = true;
        }
        break;
    }
    // TODO
    default: {
        break;
    }
    }

    _->rqst.update = false;
    return 0;
}

int on_body(http_parser* _, const char* at, size_t length) {
    (void)_;
    //printf("Body: %.*s\n", (int)length, at);
    _->rqst.body = std::string_view(at, length);
    return 0;
}
