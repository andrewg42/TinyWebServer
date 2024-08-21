#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <cassert>
#include <sys/epoll.h>

constexpr int MAX_EVENT_NUMBER = 100;

int main() {
    int listen_fd = ::socket(AF_INET, SOCK_STREAM, 0);
    assert(-1 != listen_fd);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(I)

    struct epoll_event events[MAX_EVENT_NUMBER];
    ep_fd = ::epoll_create1();
    assert(-1 != ep_fd);
}