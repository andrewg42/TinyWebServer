#pragma once

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
    std::atomic<bool> running; // flag indicating whether the log is running
    Log_Level min_level; // threshold
    std::string const base_name; // base directory of log files
    std::unique_ptr<Buffer> p_cur, p_next; // ping-pong buffer
    std::thread backend; // logging thread
    std::mutex mtx_buffer; // make frontend thread safe
    std::condition_variable cv_buffer_not_full; // signal waiting threads that data has been appended
    std::mutex mtx_flush;
    std::condition_variable cv_need_flush; // signal the receiver when to write to the disk

public:
    // ctor
    explicit Log(std::string const &base_name_ = "/tmp/")
    : base_name(base_name_), min_level(Log_Level::info),
    p_cur(std::make_unique<Buffer>()),
    p_next(std::make_unique<Buffer>()) {
        start();
    }

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
    void ping_pong();

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

#define LOG_DEBUG(...) \
    log::Log &log = log::Log::instance(); \
    log.log_debug(__VA_ARGS__);


} // namespace webserver
