#pragma once

#include <chrono>
#include <functional>
#include <netinet/in.h>

using Timer_Stamp_t = std::chrono::system_clock::time_point;
using Callback_t = std::function<void()>;
using New_Conn_Callback_t = std::function<void(int const, sockaddr_in const &)>;

static constexpr std::size_t LOG_BUFF_SZ = 4096; // for log::Buffer::buffer
static constexpr std::size_t EVENT_LIST_SZ = 1024; // for net::Reactor::event_list
static constexpr std::size_t THREADPOOL_SZ = 512;

static constexpr std::size_t READ_BUFFER_SZ = 2048; // for net::Http_Conn::read_buffer
static constexpr std::size_t WRITE_BUFFER_SZ = 1024; // for net::Http_Conn::write_buffer

static int cfg_port = 2024;
static int cfg_sql_conn_num = 8;
static int cfg_thread_num = 8;