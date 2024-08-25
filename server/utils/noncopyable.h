#pragma once

namespace server {
namespace utils {

struct Noncopyable {
  Noncopyable() = default;
  virtual ~Noncopyable() = default;

  Noncopyable(Noncopyable &) = delete;
  Noncopyable &operator=(Noncopyable &) = delete;
};

} // namespace utils
} // namespace server
