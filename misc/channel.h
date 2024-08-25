#pragma once

#include <cstdint>
#include <memory>
#include <optional>
#include <server/config.h>
#include <server/log/log.h>
#include <server/utils/file_handler.h>
#include <server/net/socket.h>

namespace server {
namespace net {

class Event_Loop;

enum class Channel_Status : unsigned char {
  removed = 0,
  added
};

/**
 * Encapsulate operators of file
 */
class Channel {
public:
  // ctor
  // only initialized by Acceptor and Http_Conn
  explicit Channel(Event_Loop *loop, int fd, uint32_t event)
      : mLoop(loop),
        mFd(fd),
        mRevent{},
        mEvent(event),
        mStatus(Channel_Status::removed),
        mIsHandling{} {}

  Channel(Channel &&) = delete;
  ~Channel() = default;

  int fd() const noexcept {
    return mFd.fileno();
  }

  auto conn() {
    return mConn.lock();
  }

  void setHolder(std::shared_ptr<Http_Conn> conn) {
    mConn = conn;
  }

  // operators for event and revent
  uint32_t event() const noexcept {
    return mEvent;
  }

  void setRevent(uint32_t revent) {
    mRevent = revent;
  }

  // operators for handling
  bool isHandling() {
    return mIsHandling;
  }

  Channel_Status status() const {
    return mStatus;
  }

  void setStatus(Channel_Status status) {
    mStatus = status;
  }

#define PER(f) f(read) f(write) f(close) f(error)

  // operators for handlers
#define FUNC_(x) \
  void set_##x##_handler(Callback_t &&x##_handler_) { \
    x##_handler = std::move(x##_handler_); \
  }
  PER(FUNC_)
#undef FUNC_

  void handleEvents(Timer_Stamp_t);

private:
  // detail implements of handle_events()
#define FUNC_(x) \
  void handle_##x() { \
    if (x##_handler) \
      x##_handler(); \
  }
  PER(FUNC_)
#undef FUNC_

#define FUNC_(x) Callback_t x##_handler;
  PER(FUNC_)
#undef FUNC_

#undef PER

  Event_Loop *mLoop;

  // intermediate layer added just because we don’t know when client socket will
  // be destroyed
  std::weak_ptr<Http_Conn> mConn;
  utils::FileHandler mFd;

  bool mIsHandling;
  uint32_t mEvent;
  uint32_t mRevent; // received event mask
  Channel_Status mStatus;
};

} // namespace net
} // namespace server
