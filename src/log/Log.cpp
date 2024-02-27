#include "Config.h"
#include "utils/Buffer.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <format>
#include <algorithm>
#include <thread>
#include <string>

#include <log/Log.h>
#include <memory>
#include <thread>

namespace webserver {
namespace log {

static const std::string LOG_DIR = "/tmp/";

Log::Log()
: base_name(LOG_DIR), min_level(Log_Level::info),
  running(false),
  p_buffer(std::make_unique<utils::Buffer<LOG_BUFF_SZ>>()),
  p_buffer_to_write(std::make_unique<utils::Buffer<LOG_BUFF_SZ>>()) {
    start();
}

void Log::start() {
    if(running) return;

    running = true;
    backend = std::thread(&Log::thread_task, this);
}

void Log::stop() {
    if(!running) return;

    running = false;
    cv.notify_one();
    if(backend.joinable()) backend.join();
}

void Log::set_level(Log_Level lev) {
    min_level = lev;
}

void Log::thread_task() {
    //std::unique_ptr<Buffer> p_buffer_to_write = std::make_unique<Buffer>();

    while(running) {
        {
            std::unique_lock lck(mtx);
            cv.wait(lck, [this]() {
                return p_buffer->cur_pos>=LOG_BUFF_SZ-1 || !running;
            });
            std::swap(p_buffer, p_buffer_to_write);
        }

        // flush buffer to the disk
        // timestamp for setting file name
        std::chrono::zoned_time now{std::chrono::current_zone(), std::chrono::high_resolution_clock::now()};
        // set name of logging file
        std::ofstream out_file(base_name + std::format("webserverlog_{}.txt", now));
        if (!out_file.is_open()) {
            std::cerr << "Failed to open the file for writing." << std::endl;
            continue;
        }

        //out_file.write(p_next->buffer.data(), p_next->buffer.size());
        out_file.write(p_buffer_to_write->buffer.data(), p_buffer_to_write->cur_pos);
        out_file.close();

        p_buffer_to_write->clear();
    }
}

static char const *loglevel2str(Log_Level lev) {
    switch(lev) {
#define _FUNCTION(name) case Log_Level::name: return #name;
    FOREACH_LOG_LEVEL(_FUNCTION)
#undef _FUNCTION
    default: return "unknown";
    }
}

void Log::log_helper(Log_Level lev, std::string const &msg) {
    std::chrono::zoned_time now{std::chrono::current_zone(), std::chrono::high_resolution_clock::now()};
    std::string log_msg = std::format("{} [{}] {}\n", now, loglevel2str(lev), msg);

    std::unique_lock lck(mtx);
    p_buffer->append(log_msg);
    if(p_buffer->cur_pos >= LOG_BUFF_SZ-1) {
        cv.notify_one();
    }
}

} // namespace webserver::log
} // namespace webserver