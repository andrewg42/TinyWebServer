#pragma once

#include <Config.h>

namespace webserver {
namespace net {

class Channel {
private:
    Callback_Func_t read_cb;
    Callback_Func_t write_cb;
    Callback_Func_t close_cb;
};

} // namespace webserver::net
} // namespace webserver