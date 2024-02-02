#pragma once

#include <utility>
#include <chrono>
#include <functional>

using Timer_Stamp_t = std::chrono::steady_clock::time_point;
using Callback_Func_t = std::function<void()>;

static constexpr std::size_t LOG_BUFF_SZ = 4096;