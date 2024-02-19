#include <net/Acceptor.h>
#include "log/Log.h"
#include "net/Http_Conn.h"
#include "net/Socket.h"
#include <net/Event_Loop.h>

namespace webserver {
namespace net {

static constexpr uint32_t default_event = EPOLLIN | EPOLLET;
static int constexpr SOCK_BACKLOG = 4096;

Acceptor::Acceptor(Event_Loop *p_loop_, int port)
: p_loop(p_loop_), Socket(::socket(PF_INET, SOCK_STREAM, 0)),
  chan(p_loop_, get_fd(), default_event) {
    if(-1 == get_fd()) {
        LOG_ERROR("socket()");
    } else {
        bind_and_listen(port);
        chan.set_read_handler(std::bind(&Acceptor::read_handler, this));
    }
}

void Acceptor::bind_and_listen(int port) {
    int const serv_fd = get_fd();

    struct sockaddr_in serv_addr;
    ::memset(&serv_addr, 0, sizeof serv_addr);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY; //::inet_addr(ip)
    serv_addr.sin_port = ::htons(port);

    if(-1 == ::bind(serv_fd, reinterpret_cast<sockaddr*>(&serv_addr), sizeof serv_addr)) {
        LOG_ERROR("bind()");
    } else {
        if(-1 == ::listen(serv_fd, SOCK_BACKLOG)) {
            LOG_ERROR("listen()");
        }
    }
}

void Acceptor::read_handler() {
    LOG_DEBUG("Acceptor::read_handler()");
    
    sockaddr_in clnt_addr;

    int clnt_fd = accept(&clnt_addr);

    if(0 > clnt_fd) {
        LOG_ERROR("accept()");
    } else {
        auto p_conn = std::make_shared<Http_Conn>(p_loop, clnt_fd);
        p_conn->init_chan();
        p_loop->add_clnt(p_conn);
    }
}

int Acceptor::accept(sockaddr_in *p_clnt_addr) {
    socklen_t clnt_addr_sz = sizeof(struct sockaddr_in);
    int clnt_sock = ::accept4(sock_fd, reinterpret_cast<sockaddr*>(p_clnt_addr),
                                &clnt_addr_sz, SOCK_NONBLOCK | SOCK_CLOEXEC);

    if (-1 == clnt_sock) {
        LOG_ERROR("socket = {}, accept()", sock_fd);
    }
    return clnt_sock;
}

} // namespace webserver::net
} // namespace webserver