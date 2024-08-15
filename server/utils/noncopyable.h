#pragma once

namespace webserver {
namespace utils {

struct Noncopyable {
  Noncopyable() = default;
  virtual ~Noncopyable() = default;

  Noncopyable(Noncopyable &) = delete;
  Noncopyable &operator=(Noncopyable &) = delete;
};

} // namespace utils
} // namespace webserver
