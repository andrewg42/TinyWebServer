#include <algorithm>
#include <chrono>
#include <fmt/core.h>
#include <fstream>
#include <iostream>
#include <memory>
#include <server/config.h>
#include <server/log/log.h>
#include <server/utils/buffer.h>
#include <string>
#include <thread>
#include <server/log/time_stamp.h>

namespace server {
namespace log {

static std::string const LOG_DIR = "/tmp/";

Log::Log()
    : base_name(LOG_DIR),
      min_level(Log_Level::info),
      running(false),
      p_buffer(std::make_unique<utils::Buffer<LOG_BUFF_SZ>>()),
      p_buffer_to_write(std::make_unique<utils::Buffer<LOG_BUFF_SZ>>()) {
  start();
}

void Log::start() {
  if (running) {
    return;
  }

  running = true;
  backend = std::thread(&Log::thread_task, this);
}

void Log::stop() {
  if (!running) {
    return;
  }

  running = false;
  cv.notify_one();
  if (backend.joinable()) {
    backend.join();
  }
}

void Log::set_level(Log_Level lev) {
  min_level = lev;
}

void Log::thread_task() {
  // std::unique_ptr<Buffer> p_buffer_to_write = std::make_unique<Buffer>();

  while (running) {
    {
      std::unique_lock lck(mtx);
      cv.wait(lck, [this]() {
        return p_buffer->cur_pos >= LOG_BUFF_SZ - 1 || !running;
      });
      std::swap(p_buffer, p_buffer_to_write);
    }

    // flush buffer to the disk
    // timestamp for setting file name
    auto now = TimeStamp::now();
    // set name of logging file
    std::ofstream out_file(base_name + fmt::format("webserverlog_{}.txt", now));
    if (!out_file.is_open()) {
      std::cerr << "Failed to open the file for writing." << std::endl;
      continue;
    }

    // out_file.write(p_next->buffer.data(), p_next->buffer.size());
    out_file.write(p_buffer_to_write->buffer.data(),
                   p_buffer_to_write->cur_pos);
    out_file.close();

    p_buffer_to_write->clear();
  }
}

static char const *loglevel2str(Log_Level lev) {
  switch (lev) {
#define _FUNCTION(name) \
  case Log_Level::name: return #name;
    FOREACH_LOG_LEVEL(_FUNCTION)
#undef _FUNCTION
  default: return "unknown";
  }
}

void Log::log_helper(Log_Level lev, std::string const &msg) {

  auto now = TimeStamp::now();
  std::string log_msg =
    fmt::format("{} [{}] {}\n", now, loglevel2str(lev), msg);

  std::unique_lock lck(mtx);
  p_buffer->append(log_msg);
  if (p_buffer->cur_pos >= LOG_BUFF_SZ - 1) {
    cv.notify_one();
  }
}

} // namespace log
} // namespace server
