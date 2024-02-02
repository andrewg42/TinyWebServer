#pragma once

#include <string>
#include <optional>

#include "http/Http_Msg.h"

namespace webserver {
namespace http {

class Http_Parser {
    std::optional<Http_Request> parse(std::string const &http_raw);

    std::string raw_msg;
};

} // namespace webserver::http
} // namespace webserver