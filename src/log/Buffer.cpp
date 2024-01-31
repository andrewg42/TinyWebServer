#include <log/Buffer.h>
#include <mutex>

namespace webserver {

namespace log {

void Buffer::append(std::string const &msg) {
    // copy message to the buffer
    auto dest = buffer.begin() + cur_pos;
    std::copy(msg.begin(), msg.end(), dest);
    // update off-set
    cur_pos = std::min(cur_pos + msg.size(), LOG_BUFF_SZ);
}

} // namespace webserver::log

} // namespace webserver
