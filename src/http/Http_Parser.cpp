#include <http/Http_Parser.h>
#include <cstddef>
#include <string_view>
#include <sstream>
#include <system_error>
#include <vector>
#include <algorithm>

namespace webserver {
namespace http {

static std::string_view trim_whitespcae(std::string_view src) {
    auto is_space = [](unsigned char c) { return !std::isspace(c); };
    auto beg = std::find_if(src.begin(), src.end(), is_space);
    auto rend = std::find_if(src.rbegin(), src.rend(), is_space);
    auto end = rend.base();
    return (end <= beg) ? std::string_view() : src.substr(beg - src.begin(), end - beg);
}

static std::vector<std::string_view> split(std::string_view src, char delimiter) {
    std::vector<std::string_view> ret;
    std::size_t beg{}, end{};

    while((end = src.find(delimiter, beg)) != std::string::npos) {
        std::string_view token = src.substr(beg, end - beg);
        ret.emplace_back(token);
        beg = end + 1;
    }

    return ret;
}

static std::vector<std::string_view> split(std::string_view src, std::string_view delimiter) {
    std::size_t const len = delimiter.size();
    std::vector<std::string_view> ret;
    std::size_t beg{}, end{};

    while((end = src.find(delimiter, beg)) != std::string::npos) {
        std::string_view token = src.substr(beg, end - beg);
        ret.push_back(token);
        beg = end + len;
    }

    return ret;
}

std::optional<Http_Request> Http_Parser::parse(std::string const &packet) {
    raw_msg.reserve(raw_msg.size() + packet.size());
    raw_msg.insert(raw_msg.end(), packet.begin(), packet.end());

    if(!raw_msg.ends_with("\r\n\r\n")) {
        return {};
    }

    Http_Request rqst;
    std::string_view full_msg(raw_msg.data(), raw_msg.size());
    std::vector<std::string_view> const lines = split(full_msg, "\r\n");
    std::vector<std::string_view> const status = split(lines[0], ' ');

    rqst.method = status[0];
    rqst.url = status[1];
    rqst.version = status[2];
    
    for(std::size_t idx=1; idx<lines.size(); ++idx) {
        std::string_view tmp = lines[idx];
        std::vector<std::string_view> header = split(tmp, ':');
        if(2 == header.size()) {
            rqst.header_list.emplace_back(std::pair(header[0], trim_whitespcae(header[1])));
        }
    }

    raw_msg.clear();
    return rqst;
}


} // namespace webserver::http
} // namespace webserver