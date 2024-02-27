#pragma once

#include <sys/epoll.h>
#include <memory>
#include <vector>

#include <net/Socket.h>
#include <http/http_parser.h>
#include "Config.h"
#include "net/Channel.h"
#include <utils/Buffer.h>
#include <utils/Noncopyable.h>

namespace webserver {
namespace net {

class Event_Loop;
class Channel;

/**
 * @brief Client socket.
 *      Notice that this class inherits from the Socket class.
 *
 */
class Http_Conn: public Socket, public std::enable_shared_from_this<Http_Conn> {
private:
    Event_Loop *p_loop; // Pointer to thr loop (for callback)
    static http_parser_settings settings;
    http_parser parser;

    std::unique_ptr<Channel> p_chan;
    utils::Buffer<READ_BUFFER_SZ> read_buffer;
    utils::Buffer<WRITE_BUFFER_SZ> write_buffer;
    std::string filename;

public:
    /**
     * @brief Construct a new Http_Conn object
     * 
     * @param p_loop_ : For p_loop
     * @param fd_ : File descriptor of client socket, for p_sock
     */
    explicit Http_Conn(Event_Loop *p_loop_, int fd_);

    /**
     * @brief Destroy the Http_Conn object
     * 
     */
    ~Http_Conn() = default;

    /**
     * @brief Initialization of p_chan 
     * 
     */
    void init_chan();

    /**
     * @brief Get the pointer p_chan
     * 
     * @return Channel* 
     */
    Channel *get_chan() { return p_chan.get(); }

private:
    void do_request();

    /**
     * @brief append message to response
     * 
     * @param str : message
     * @return true : append successfully
     * @return false : have some error
     */
    bool append_response(std::string_view str);
    
    bool add_headers(std::size_t content_len);
    bool add_content_length(std::size_t content_len);
    bool add_content_type();
    bool add_linger();
    bool add_blank_line();

    /**
     * @brief generate response based on http_parser
     * 
     * @return true : generate response successfully
     * @return false : have error
     */
    bool gen_response();

    /**
     * @brief 
     * 
     */
    void read_handler();

    /**
     * @brief 
     * 
     */
    void write_handler();

    /**
     * @brief 
     * 
     */
    void close_handler();

    /**
     * @brief 
     * 
     */
    void error_handler();
};

} // namespace webserver::net
} // namespace webserver