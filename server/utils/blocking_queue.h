#pragma once

#include <array>
#include <condition_variable>
#include <mutex>
#include <server/utils/noncopyable.h>

namespace webserver {
namespace utils {

template <class T, std::size_t N>
struct Blocking_Queue : public webserver::utils::Noncopyable {
  // ref:
  // https://github.com/openjdk/jdk/blob/master/src/java.base/share/classes/java/util/concurrent/ArrayBlockingQueue.java
  using value_type = T;

  Blocking_Queue() : take_idx{}, put_idx{}, count{} {}

  ~Blocking_Queue() = default;

  void push(T const &value) {
    std::unique_lock<std::mutex> lck(mtx);
    cv.wait(lck, [this] { return count < N; });

    buffer[put_idx] = value;
    put_idx = (put_idx + 1) % MAX_SIZE;

    lck.unlock();
    cv.notify_one();
  }

  void push(T &&value) {
    std::unique_lock<std::mutex> lck(mtx);
    cv.wait(lck, [this] { return count < N; });

    buffer[put_idx] = std::move(value);
    put_idx = (put_idx + 1) % MAX_SIZE;

    lck.unlock();
    cv.notify_one();
  }

  [[nodiscard]] T pop() {
    std::unique_lock<std::mutex> lck(mtx);
    cv.wait(lck, [this] { return !this->empty(); });

    T value = std::move(buffer[take_idx]);
    take_idx = (take_idx + 1) % MAX_SIZE;

    lck.unlock();
    cv.notify_one();
    return value;
  }

private:
  // (need mutex)
  bool empty() {
    return take_idx == put_idx;
  }

  static constexpr std::size_t MAX_SIZE = N + 1;
  std::array<T, MAX_SIZE> buffer; // ring buffer
  std::size_t count;

  std::mutex mtx;
  std::condition_variable cv;
  std::size_t take_idx;
  std::size_t put_idx;
};

} // namespace utils
} // namespace webserver
