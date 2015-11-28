#include "thread_pool.h"

#include <cassert>

thread_pool* thread_pool::instance_ = 0;

void thread_pool::instantiate()
{
  assert(0 == instance_);
  instance_ = new thread_pool(10);
}

thread_pool& thread_pool::instance()
{
  assert(0 != instance_);
  return *instance_;
}

void thread_pool::destroy()
{
  delete instance_;
  instance_ = 0;
}

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
            std::unique_lock<std::mutex> lock(this->queue_mutex_);
            this->condition_.wait(lock, [this]{ return this->stop_ || !this->tasks_.empty(); });
            if(this->stop_ && this->tasks_.empty())
            {
              return;
            }
            task = std::move(this->tasks_.front());
            this->tasks_.pop();
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

