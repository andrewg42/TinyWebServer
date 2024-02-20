#include <net/Http_Conn.h>

#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>

#include <net/Channel.h>
#include <net/Event_Loop.h>
#include <net/Socket.h>
#include <log/Log.h>

#include <http/Http_Parser.h>
#include <fstream>
#include <sstream>
#include "http/http_parser.h"

namespace webserver {
namespace net {

static constexpr uint32_t default_event = EPOLLIN | EPOLLET | EPOLLONESHOT;
static constexpr std::size_t READ_BUFFER_SZ = 1024;
static std::map<std::string_view, std::string const> const url2file = {
    {"/0", "../root/judge.html"},
};


Http_Conn::Http_Conn(Event_Loop *p_loop_, int fd_)
: p_loop(p_loop_),
  Socket(fd_),
  p_chan(std::make_unique<Channel>(p_loop_, fd_, default_event)),
  read_buffer(READ_BUFFER_SZ) {
}

void Http_Conn::init_chan() {
    LOG_DEBUG("Http_Conn::init_chan()");
    p_chan->set_holder(shared_from_this());
    p_chan->set_read_handler(std::bind(&Http_Conn::read_handler, this));
    p_chan->set_write_handler(std::bind(&Http_Conn::write_handler, this));
    p_chan->set_close_handler(std::bind(&Http_Conn::close_handler, this));
    p_chan->set_error_handler(std::bind(&Http_Conn::error_handler, this));
}

void Http_Conn::read_handler() {
    LOG_DEBUG("Http_Conn::read_handler()");

    // read from socket fd
    int read_bytes, read_bytes_tot{};
    int read_step = READ_BUFFER_SZ;
    while(true) {
        int read_bytes = ::recv(get_fd(), read_buffer.data() + read_bytes_tot, READ_BUFFER_SZ, 0);
        if(0 == read_bytes) { // socket has been closed
            // just wait timer to remove it
            return;
        }
        else if(0 > read_bytes) {
            if(errno == EAGAIN) { // finish read
                LOG_DEBUG("total read {} bytes", read_bytes_tot);
                read_buffer.resize(read_bytes_tot);
                break;
            }
        }
        else { // need continue reading
            read_bytes_tot += read_bytes;
            if(read_bytes_tot >= read_buffer.size()) {
                read_buffer.resize(read_buffer.size() * 2);
            } 
        }
    }

    // parse HTTP
    http_parser_settings settings = {
        on_message_begin,
        on_url,
        nullptr,
        on_header_field,
        on_header_value,
        on_headers_complete,
        on_body,
        on_message_complete,
    };

    http_parser parser;
    http_parser_init(&parser, HTTP_REQUEST);
    http_parser_execute(&parser, &settings, read_buffer.data(), read_buffer.size());

    gen_response(parser);

    read_buffer.clear();
}

void Http_Conn::gen_response(http_parser &parser) {
    if(parser.method == HTTP_GET) {
        if(!parser.rqst.done) return;
        auto it = url2file.find(parser.rqst.url);
        if(it == url2file.end()) return;

        std::ifstream file(it->second.c_str(), std::ifstream::in);
        if(!file.is_open()) {
            LOG_ERROR("open file {}", it->second);
        }

        std::string response_header = "HTTP/1.1 200 OK\r\n";
        response_header += "Content-Type: test/plain\r\n";
        response_header += "\r\n";
        std::copy(response_header.begin(), response_header.end(), write_buffer.begin());

        
    }
    else if(parser.method == HTTP_POST) {
        if(!parser.rqst.done) return;
        std::cout << "POST" << '\n';
    }

    write_handler();
}

void Http_Conn::write_handler() {
    LOG_DEBUG("Http_Conn::write_handler()");

    while(true) {
        // TODO
    }
}

void Http_Conn::close_handler() {
    LOG_DEBUG("Http_Conn::close_handler()");
}

void Http_Conn::error_handler() {
    LOG_ERROR("http connection error, fd = {}", get_fd());
}

} // namespace webserver::net
} // namespace webserver