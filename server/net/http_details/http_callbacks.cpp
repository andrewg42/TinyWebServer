#include <server/net/http_details/http_callbacks.h>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <string_view>

namespace webserver {
namespace net {
namespace http {

#define HTTP_HEADER_FIELD_MAP(XX)           \
    XX(CONNECTION, "Connection")            \
    XX(CONTENT_LENGTH, "Content-Length")    \


enum class Http_Header_Field: unsigned char
{   
#define _FUNC(n, s) n,
    HTTP_HEADER_FIELD_MAP(_FUNC)
#undef _FUNC
};

static std::map<std::string_view, Http_Header_Field> http_header_field_mp =
{
#define _FUNC(n, s) {s, Http_Header_Field::n},
    HTTP_HEADER_FIELD_MAP(_FUNC)
#undef _FUNC
};

int on_message_begin(http_parser* _) {
    (void)_;
    //printf("\n***MESSAGE BEGIN***\n\n");
    return 0;
}

int on_headers_complete(http_parser* _, const char *at, size_t length) {
    if(!_->content_length) return 0;
    _->body = std::string_view(at+length+1, _->content_length);
    return 0;
}

int on_method(http_parser* _) {
    if(_->method == HTTP_DELETE) _->http_errno = HPE_INVALID_METHOD;
    return 0;
}

int on_url(http_parser* _, const char* at, size_t length) {
    _->url = std::string_view(at, length);
    //printf("Url: %.*s\n", (int)length, at);
    return 0;
}

int on_http_version(http_parser* _, const char* at, size_t length) {
    std::string_view version_view(at, length);

    std::size_t const slash_pos = version_view.find_first_of('/');
    if(std::string_view::npos != slash_pos &&
        version_view[slash_pos+1]=='1' &&
        version_view[slash_pos+3]=='1') { // only support HTTP/1.1
        _->http_major = 1;
        _->http_minor = 1;
    } else {
        if(_->http_errno == HPE_UNKNOWN) _->http_errno = HPE_INVALID_VERSION;
    }
    return 0;
}

int on_header_field(http_parser* _, const char* at, size_t length) {
    // update header fields
    _->header_field = std::string_view(at, length);
    //printf("Header field: %.*s\n", (int)length, at);
    return 0;
}

int on_header_value(http_parser* _, const char* at, size_t length) {
    // parse header fields and values
    auto it = http_header_field_mp.find(_->header_field);
    if(http_header_field_mp.end() == it) return 0;
    std::string_view value_view(at, length);

    Http_Header_Field field_mark = it->second;
    switch (field_mark) {
    case Http_Header_Field::CONNECTION: {
        if(value_view == "keep-alive") {
            _->connection = true;
        }
        break;
    }
    case Http_Header_Field::CONTENT_LENGTH: {
        _->content_length = (uint64_t)atoi(at);
        break;
    }

    // TODO
    }

    //printf("Header value: %.*s\n", (int)length, at);
    return 0;
}

int on_body(http_parser* _, const char* at, size_t length) {
    _->body = std::string_view(at, length);
    //printf("Body: %.*s\n", (int)length, at);
    _->http_errno = HPE_OK;
    return 0;
}

} // namespace webserver::net::http
} // namespace webserver::net
} // namespace webserver