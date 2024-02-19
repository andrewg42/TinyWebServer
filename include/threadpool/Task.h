#pragma once

#include <functional>
#include <memory>

#include <utils/Noncopyable.h>

namespace webserver {
namespace threadpool {

class Task: public utils::Noncopyable {
private:
    struct Task_Base {
        Task_Base() = default;
        virtual ~Task_Base() = default;

        virtual void call() = 0;
    };

    template <class F, class T = typename std::decay<F>::type>
    struct Task_Derived: Task_Base {
        T func;
        explicit Task_Derived(F &&func_): func(std::move(func_)) {}

        void call() override { func(); }
    };

    std::unique_ptr<Task_Base> p_func = nullptr;
    int priority = 0;

public:
    Task() = default;

    template <class F>
    explicit Task(F &&f, int pr_ = 0)
    : p_func(new Task_Derived<F>(std::forward<F>(f))),
      priority(pr_) {}

    ~Task() = default;

    Task(Task &&rhs) noexcept
    : p_func(std::move(rhs.p_func)), priority(rhs.priority) {}

    Task &operator=(Task &&rhs) noexcept {
        p_func = std::move(rhs.p_func);
        priority = rhs.priority;
        return *this;
    }

    bool operator>(Task const &rhs) const { return priority < rhs.priority; }
    bool operator<(Task const &rhs) const { return priority > rhs.priority; }
};
    
} // namespace webserver::threadpool
} // namespace webserver