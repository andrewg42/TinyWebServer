#pragma once

namespace webserver {

namespace net {

class Reactor {
// ref: https://github.com/an-tao/trantor
private:
    int ep_fd;
    bool is_running;

public:
    Reactor();
    ~Reactor();

    void run();
    void ep_add(int fd);
    void ep_remove(int fd);
    void ep_mode(int fd);
};

} // namespace webserver::net

} // namespace webserver