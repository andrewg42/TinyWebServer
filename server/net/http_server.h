#pragma once
#include <memory>

namespace server {
namespace net {

struct HTTPServer {
  HTTPServer();

private:
  struct Impl;
  std::unique_ptr<Impl> mImpl;
};

} // namespace net
} // namespace server
