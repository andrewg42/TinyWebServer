#pragma once

#include <array>
#include <cstring>
#include <string>
#include <memory>

#include <Config.h>

namespace webserver {

namespace utils {

template<std::size_t N>
struct Buffer {
    std::array<char, N> buffer;
    std::size_t cur_pos; // off-set

    // ctor
    Buffer() { clear(); }

    // init buffer
    void clear() {
        memset(buffer.data(), 0, sizeof buffer);
        cur_pos = 0;
    }
    
    // add message to buffer (need mutex)
    // bool append(std::string const &msg);
    bool append(std::string_view msg) {
        // copy message to the buffer
        auto dest = buffer.begin() + cur_pos;
        std::copy(msg.begin(), msg.end(), dest);
        // update off-set
        cur_pos = std::min(cur_pos + msg.size(), N-1);
        return cur_pos == N-1;
    }

    char const *data() const noexcept { return buffer.data(); }

    std::size_t size() const noexcept { return cur_pos; }

    std::size_t capacity() const noexcept { return N; }

    void resize(std::size_t const sz) { cur_pos = sz; }
};

} // namespace webserver::utils

} // namespace webserver