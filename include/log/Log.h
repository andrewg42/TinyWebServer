#pragma once

#include <iostream>
#include <condition_variable>
#include <format>
#include <cstring>
#include <string>
#include <chrono>
#include <string_view>

#include <Config.h>
#include <utils/Blocking_Queue.h>
#include <utils/Singleton.h>
#include <log/Buffer.h>

namespace webserver {

namespace log {

// ref: https://github.com/archibate/minilog
#define FOREACH_LOG_LEVEL(f) \
    f(trace) \
    f(debug) \
    f(info) \
    f(critical) \
    f(warn) \
    f(error) \
    f(fatal)

enum class Log_Level: unsigned char {
#define _FUNCTION(name) name,
    FOREACH_LOG_LEVEL(_FUNCTION)
#undef _FUNCTION
};

class Log: public utils::Singleton<Log> {
// ref: https://github.com/chenshuo/muduo/blob/master/muduo/base/AsyncLogging.h
// sender --> buffer -receiver-> disk
private:
    // 
    std::atomic<bool> running; // flag indicating whether the log is running
    std::string const base_name; // base directory of log files
    std::unique_ptr<Buffer> p_cur, p_next; // ping-pong buffer
    std::thread backend; // logging thread
    std::mutex mtx;
    std::condition_variable cv;

public:
    Log_Level min_level; // threshold

    // ctor
    explicit Log(std::string const &base_name_ = "/tmp/");

    // dtor
    ~Log() { stop(); }

    // start log
    void start();

    // stop log
    void stop();

    // set the threshold of log level
    void set_level(Log_Level lev);

    // write log with log level
#define _FUNCTION(name) \
    template <class... Args> \
    void log_##name( \
        std::format_string<Args...> fmt, \
        Args&&... args) { \
        generic_log(Log_Level::name, std::move(fmt), std::forward<Args>(args)...); \
    }
    FOREACH_LOG_LEVEL(_FUNCTION)
#undef _FUNCTION
    
private:
    // swap pointers of two buffers, and notice backend thread, when:
    //  1. buffer is full
    //  2. log is stopped

    // task of logging thread
    void thread_task();

    // flush buffer to the disk
    void flush();

    // implement of log_##name
    // ref: https://en.cppreference.com/w/cpp/utility/format/vformat
    template <class ...Args>
    void generic_log(Log_Level lev, std::format_string<Args...> fmt, Args &&...args) {
        if(lev < min_level) return;

        std::string msg = std::vformat(fmt.get(), std::make_format_args(args...));
        log_helper(lev, msg);
    }

    // common interface to all partial specialization types
    void log_helper(Log_Level lev, std::string const &msg);

};

} // namespace webserver::log
#define LOG_TRACE(...) \
    do { \
        webserver::log::Log &log = webserver::log::Log::instance(); \
        if(log::Log_Level::trace >= log.min_level) { \
            log.log_trace(__VA_ARGS__); \
        } \
    } while(0);

#define LOG_DEBUG(...) \
    do { \
        webserver::log::Log &log = webserver::log::Log::instance(); \
        if(log::Log_Level::debug >= log.min_level) { \
            log.log_debug(__VA_ARGS__); \
        } \
    } while(0);

#define LOG_ERROR(...) \
    do { \
        webserver::log::Log &log = webserver::log::Log::instance(); \
        log.log_error(__VA_ARGS__); \
    } while(0);

#define LOG_CLEANUP \
    do { \
        webserver::log::Log &log = webserver::log::Log::instance(); \
        log.stop(); \
    } while(0);
} // namespace webserver
