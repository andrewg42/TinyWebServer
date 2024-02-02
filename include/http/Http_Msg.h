#pragma once

#include <string>
#include <vector>
#include <utility>
#include <sstream>

namespace webserver {
namespace http {

struct Http_Request {
    std::string method;
    std::string url;
    std::string version;
    std::vector<std::pair<std::string, std::string>> header_list;
};

struct Http_Response {
    std::string version;
    std::string status;
    std::string status_text;
    std::vector<std::pair<std::string, std::string>> header_list;

    std::string serialize() const {
        std::stringstream resp;
        resp << version << ' ' << status << ' ' << status_text << "\r\n";
        for(auto &p:header_list) {
            resp << p.first << ':' << p.second << "\r\n";
        }
        resp << "\r\n";
        return resp.str();
    }
};

} // namespace webserver::http
} // namespace webserver