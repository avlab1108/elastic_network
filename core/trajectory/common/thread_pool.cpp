#include "thread_pool.h"

#include <iostream>

// the constructor just launches some amount of workers
thread_pool::thread_pool(const size_t threads) :
  stop_(false)
{
  for(size_t i = 0; i < threads; ++i)
  {
    workers_.emplace_back(
      [this]
      {
        for(;;)
        {
          std::function<void()> task;
          {
            std::unique_lock<std::mutex> lock(queue_mutex_);
            condition_.wait(lock, [this]{ return stop_ || !tasks_.empty(); });
            if(stop_ && tasks_.empty())
            {
              return;
            }
            task = std::move(tasks_.front());
            tasks_.pop();
          }
          task();
        }
      });
  }
}

// the destructor joins all threads
thread_pool::~thread_pool()
{
  {
    std::unique_lock<std::mutex> lock(queue_mutex_);
    stop_ = true;
  }
  condition_.notify_all();
  for(std::thread& worker : workers_)
  {
    worker.join();
  }
}

