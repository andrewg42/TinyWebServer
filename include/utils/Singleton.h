#pragma once

#include <utility>

namespace webserver {

namespace utils {

template <class T>
struct Singleton {
// ref: CppCon 2018: Greg Falcon “Initialization, Shutdown, and constexpr”
    Singleton() = default;
    virtual ~Singleton() = default;

    Singleton(Singleton const&) = delete;
    Singleton &operator=(Singleton const&) = delete;
    Singleton(Singleton const&&) = delete;
    Singleton &operator=(Singleton const&&) = delete;

    template <class... Args>
    static T &instance(Args &&... args) {
        static T _instance(std::forward<Args>(args)...);
        return _instance;
    }
};

} // namespace webserver::utils

} // namespace webserver