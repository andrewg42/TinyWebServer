#pragma once

#include <chrono>
#include <ctime>
#include <string_view>
#include <fmt/core.h>

namespace webserver {
namespace log {

struct TimeStamp {
    static std::string_view now() {
        auto stNow = std::chrono::system_clock::now();

        std::time_t ptNow = std::chrono::system_clock::to_time_t(stNow);

        std::tm *ltNow = std::localtime(&ptNow);

        return fmt::format("{:04}-{:02}-{:02} {:02}:{:02}:{:02}",
                ltNow->tm_year + 1900,
                ltNow->tm_mon + 1,
                ltNow->tm_mday,
                ltNow->tm_hour,
                ltNow->tm_min,
                ltNow->tm_sec
            );
    }
};

}
}