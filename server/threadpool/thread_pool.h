#pragma once

#include <future>
#include <queue>
#include <server/config.h>
#include <server/utils/blocking_queue.h>
#include <server/utils/singleton.h>
#include <thread>
#include <vector>

namespace server {
namespace threadpool {

struct Thread_Pool : public utils::Singleton<Thread_Pool> {
public:
  // ctor
  explicit Thread_Pool(std::size_t thread_num) : m_stop{} {
    std::size_t const hardward_thread_num = std::thread::hardware_concurrency();
    thread_num =
      std::min(0 != hardward_thread_num ? hardward_thread_num : 2, thread_num);
    for (std::size_t i{}; i < thread_num; ++i) {
      m_workers.emplace_back([this] {
        while (true) {
          std::function<void()> task;
          {
            std::unique_lock<std::mutex> lck(m_mtx);
            this->m_cv.wait(
              lck, [this] { return this->m_stop || this->m_tasks.empty(); });
            if (this->m_stop && this->m_tasks.empty()) {
              return;
            }
            task = std::move(this->m_tasks.front());
            this->m_tasks.pop();
          }
        }
      });
    }
  }

  // dtor
  ~Thread_Pool() {
    {
      std::unique_lock<std::mutex> lck(m_mtx);
      m_stop = true;
    }
    m_cv.notify_all();
    for (auto &worker: m_workers) {
      worker.join();
    }
  }

  // TODO: use lambda expression
  template <class Func, class... Args>
  auto enqueue(Func &&func, Args &&...args)
    -> std::future<typename std::result_of_t<Func(Args...)>> {
    using Ret = typename std::result_of_t<Func(Args...)>;
    auto task = std::make_shared<std::packaged_task<Ret()>>(
      std::bind(std::forward<Func>(func), std::forward<Args...>(args)...));
    std::future<Ret> ret = task->get_future();
    {
      std::unique_lock<std::mutex> lck(m_mtx);
      if (m_stop) {
        // TODO: use errno
        throw std::runtime_error("enqueue on stopped Thread Pool");
      }
      m_tasks.emplace([task]() { (*task)(); });
    }
  }

private:
  std::vector<std::thread> m_workers;
  std::queue<std::function<void()>> m_tasks;
  std::mutex m_mtx;
  std::condition_variable m_cv;
  bool m_stop;
};

} // namespace threadpool
} // namespace server
