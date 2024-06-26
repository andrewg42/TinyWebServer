#pragma once

#include <server/config.h>
#include <server/utils/singleton.h>
#include <server/utils/blocking_queue.h>
#include <server/threadpool/task.h>
#include <thread>

namespace webserver {
namespace threadpool {

class Thread_Pool: public utils::Singleton<Thread_Pool> {
// ref: https://github.com/ChunelFeng/CThreadPool/blob/main/src/UtilsCtrl/ThreadPool/UThreadPool.h
private:
    std::size_t thread_number;
    utils::Blocking_Queue<Task, THREADPOOL_SZ> task_queue;
    std::vector<std::thread> thread_vec;

public:
    // ctor
    explicit Thread_Pool(std::size_t thread_num_) {
        std::size_t const hardward_thread_num = std::thread::hardware_concurrency();
        thread_number = std::min(0 != hardward_thread_num ? hardward_thread_num : 2, thread_num_);
    }

    // dtor
    ~Thread_Pool() {
        for(auto &t:thread_vec) {
            if(t.joinable()) t.join();
        }
    }
    
    void run();

private:

};

} // namespace webserver::threadpool
} // namespace webserver