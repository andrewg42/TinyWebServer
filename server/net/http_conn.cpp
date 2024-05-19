#include <server/net/http_conn.h>
#include <server/log/log.h>
#include <server/net/channel.h>
#include <server/net/event_loop.h>
#include <server/net/socket.h>
#include <server/net/http_details/http_callbacks.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <memory>
#include <format>
#include <string>
#include <string_view>
#include <map>

namespace webserver {
namespace net {


static constexpr uint32_t default_event = EPOLLIN | EPOLLET | EPOLLONESHOT;
static constexpr std::size_t READ_BUFFER_SZ = 2048;
static constexpr std::size_t WRITE_BUFFER_SZ = 1024;
#define XX(num, name, str) static std::string_view _##num = "HTTP/1.1 " #num " " #str  "\r\n";
HTTP_STATUS_MAP(XX)
#undef XX

static std::string_view _200_form = "<html><body></body></html>";
static std::string_view _400_form = "Your request has bad syntax or is inherently impossible to staisfy.\n";
static std::string_view _403_form = "You do not have permission to get file form this server.\n";
static std::string_view _404_form = "The requested file was not found on this server.\n";
static std::string_view _500_form = "There was an unusual problem serving the request file.\n";


static std::map<std::string_view const, std::string_view const> const url2file =
{   {"/", "../root/register.html"}
,   {"/0", "../root/register.html"}
,   {"/1", "../root/log.html"}
,   {"/2", "../root/welcome.html"}
,   {"/5", "../root/picture.html"}
,   {"/6", "../root/video.html"}
};

http_parser_settings Http_Conn::settings = {
    nullptr,
    http::on_method,
    http::on_url,
    http::on_http_version,
    http::on_header_field,
    http::on_header_value,
    http::on_headers_complete,
};

Http_Conn::Http_Conn(Event_Loop *p_loop_, int fd_)
: p_loop(p_loop_),
  Socket(fd_),
  p_chan(std::make_unique<Channel>(p_loop_, fd_, default_event)),
  file_addr(nullptr), iv_cnt{} {}

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
    std::size_t read_bytes, read_bytes_tot{};
    constexpr std::size_t read_step = READ_BUFFER_SZ>>1;
    while(true) {
        int read_bytes = ::recv(get_fd(), (void*)(read_buffer.data() + read_bytes_tot), read_step, 0);
        if(0 == read_bytes) { // socket has been closed, just wait timer to remove it
            
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
            if(read_bytes_tot >= READ_BUFFER_SZ) {
                // any good way?
                LOG_ERROR(" HTTP messsage is too big, {} bytes have been read", read_bytes_tot);
                read_buffer.resize(read_buffer.capacity());
                break;
            } 
        }
    }

    http_parser_init(&parser, HTTP_REQUEST);
    http_parser_execute(&parser, &settings, read_buffer.data(), read_buffer.size());

    // set status code
    if(parser.http_errno == HPE_OK) do_request();
    else parser.status_code = HTTP_STATUS_BAD_REQUEST;

    // generate response
    auto rc = gen_response();
    if(!rc) { // error on generate response, close socket and wait timer to remove it
        
    }
    else if(iv_cnt != 2) {
        iv[0].iov_base = (void *)write_buffer.data();
        iv[0].iov_len = write_buffer.size();
        iv_cnt = 1;
    }

    read_buffer.clear(); // maybe should continue to parse
}

void Http_Conn::do_request() { // TODO
    auto it = url2file.find(parser.url);
    if(it == url2file.end()) { // 403 or 404
        parser.status_code = HTTP_STATUS_NOT_FOUND;
        return;
    }

    // file operations
    if(parser.method == HTTP_GET) [[likely]] {
        filename = it->second;
        LOG_DEBUG("GET request, file name = {}", filename);
    } else if(parser.method == HTTP_POST) {
        // TODO: parse the name and password
        LOG_DEBUG("POST request, request body = {}", parser.body);
    }

    if(stat(filename.c_str(), &file_stat) < 0) { // 404
        parser.status_code = HTTP_STATUS_NOT_FOUND;
        return;
    }
    if(!(file_stat.st_mode & S_IROTH)) { // 403
        parser.status_code = HTTP_STATUS_FORBIDDEN;
        return;
    }
    if(S_ISDIR(file_stat.st_mode)) { // 400
        parser.status_code = HTTP_STATUS_BAD_REQUEST;
    }

    int fd = ::open(filename.c_str(), O_RDONLY);
    // zero-copy with mmap()
    file_addr = reinterpret_cast<char *>(::mmap(0, file_stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0));
    ::close(fd);
}

void Http_Conn::unmap() {
    if (file_addr) {
        munmap(file_addr, file_stat.st_size);
        file_addr = 0;
    }
}

bool Http_Conn::append_response(std::string_view str) {
    return write_buffer.append(str);
}

bool Http_Conn::add_headers(std::size_t content_len) {
    return add_content_length(content_len) && add_linger() &&
           add_blank_line();
}

bool Http_Conn::add_content_length(std::size_t content_len) {
    std::string const msg = std::format("Content-Length: {}\r\n", content_len);
    return append_response(msg);
}

bool Http_Conn::add_content_type() {
    return append_response("Content-Type:text/html\r\n");
}

bool Http_Conn::add_linger() {
    std::string const msg = std::format("Content-Length: {}\r\n", (parser.connection == true) ? "keep-alive" : "close");
    return append_response(msg);
}

bool Http_Conn::add_blank_line() {
    return append_response("\r\n");
}

bool Http_Conn::gen_response() {
    switch (parser.status_code) {
    case HTTP_STATUS_OK: { // 200
        if(0 != file_stat.st_size) {
            if(append_response(_200) &&
            add_headers(file_stat.st_size)) {
                iv[0].iov_base = (void *)write_buffer.data();
                iv[0].iov_len = write_buffer.size();
                iv[1].iov_base = file_addr;
                iv[1].iov_len = file_stat.st_size;
                iv_cnt = 2;
                return true;
            }
        }
        else {
            return append_response(_200)
                && add_headers(_200_form.size())
                && append_response(_200_form);
        }
        break;
    }
    case HTTP_STATUS_BAD_REQUEST: { // 400
        return append_response(_400)
            && add_headers(_400_form.size())
            && append_response(_400_form);
    }
    case HTTP_STATUS_NOT_FOUND: { // 404
        return append_response(_404)
            && add_headers(_404_form.size())
            && append_response(_404_form);
    }
    default:
        break;
    }
    return false;
}

void Http_Conn::write_handler() {
    LOG_DEBUG("Http_Conn::write_handler()");

    // while(true) {
    //     // TODO
    // }
}

void Http_Conn::close_handler() {
    LOG_DEBUG("Http_Conn::close_handler()");
}

void Http_Conn::error_handler() {
    LOG_ERROR("http connection error, fd = {}", get_fd());
}

} // namespace webserver::net
} // namespace webserver