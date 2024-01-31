#pragma once

#include <array>
#include <cstring>
#include <string>
#include <memory>

#include <Config.h>

namespace webserver {

namespace log {

struct Buffer {
    std::array<char, LOG_BUFF_SZ> buffer;
    std::size_t cur_pos; // off-set

    // ctor
    Buffer() { clear(); }

    // init buffer
    void clear() {
        memset(buffer.data(), 0, sizeof buffer);
        cur_pos = 0;
    }
    
    // add message to buffer (need mutex)
    void append(std::string const &msg);
};

} // namespace webserver::log

} // namespace webserver