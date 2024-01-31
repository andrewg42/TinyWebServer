#include "Config.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <format>
#include <algorithm>

#include <log/Log.h>
#include <memory>

namespace webserver {

namespace log {

void Log::start() {
    running = true;
    backend = std::thread([this] {
        thread_task();
    });
}

void Log::stop() {
    running = false;
    ping_pong();
    if(backend.joinable()) {
        backend.join();
    }
}

void Log::set_level(Log_Level lev) {
    min_level = lev;
}

void Log::ping_pong() {
    std::swap(p_cur, p_next);
    cv_need_flush.notify_one();
}

void Log::thread_task() {
    while(running) {
        std::unique_lock<std::mutex> lck(mtx_flush);
        cv_need_flush.wait(lck, [this]() {
            return p_next->cur_pos==LOG_BUFF_SZ || !running;
        });

        flush();
    }
}

void Log::flush() {
    // timestamp for setting file name
    std::chrono::zoned_time now{std::chrono::current_zone(), std::chrono::high_resolution_clock::now()};
    
    // set name of logging file
    std::ofstream out_file(base_name + std::format("webserverlog_{}.txt", now));
    if (!out_file.is_open()) {
        std::cerr << "Failed to open the file for writing." << std::endl;
        return;
    }

    //out_file.write(p_next->buffer.data(), p_next->buffer.size());
    out_file.write(p_next->buffer.data(), p_next->cur_pos);
    out_file.close();

    p_next->clear();
}

static std::string to_str(Log_Level lev) {
    switch(lev) {
#define _FUNCTION(name) case Log_Level::name: return #name;
    FOREACH_LOG_LEVEL(_FUNCTION)
#undef _FUNCTION
    }
    return "unknown";
}

void Log::log_helper(Log_Level lev, std::string const &msg) {
    std::chrono::zoned_time now{std::chrono::current_zone(), std::chrono::high_resolution_clock::now()};
    std::string log_msg = std::format("{} [{}] {}\n", now, to_str(lev), msg);

    std::unique_lock<std::mutex> lck(mtx_buffer);
    cv_buffer_not_full.wait(lck, [this]() {
        return p_cur->cur_pos<LOG_BUFF_SZ;
    });

    p_cur->append(log_msg);

    if(p_cur->cur_pos==LOG_BUFF_SZ) {
        ping_pong();
    }
    cv_buffer_not_full.notify_one();
}

} // namespace webserver::log

} // namespace webserver