#pragma once

#include <unistd.h>
#include <utility>

namespace server {
namespace utils {

struct [[nodiscard]] FileHandler {
  FileHandler() noexcept : mFileno(-1) {}

  explicit FileHandler(int fileno) noexcept : mFileno(fileno) {}

  FileHandler(FileHandler &&rhs) noexcept : mFileno(rhs.releaseFile()) {}

  FileHandler &operator=(FileHandler &&rhs) noexcept {
    std::swap(mFileno, rhs.mFileno);
    return *this;
  }

  virtual ~FileHandler() {
    if (-1 != mFileno) {
      ::close(mFileno);
    }
  }

  int fileno() const noexcept {
    return mFileno;
  }

  int releaseFile() noexcept {
    int rc = mFileno;
    mFileno = -1;
    return rc;
  }

  explicit operator bool() noexcept {
    return -1 != mFileno;
  }

private:
  int mFileno;
};
} // namespace net
} // namespace server
