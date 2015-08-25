/*
 * Copyright 2015 Canonical Ltd.
 *
 * This file is part of unity-js-scopes.
 *
 * unity-js-scopes is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * unity-js-scopes is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _UNITY_JS_EVENT_QUEUE_H_
#define _UNITY_JS_EVENT_QUEUE_H_

#include <condition_variable>
#include <uv.h>

class EventQueue
{
public:
  inline static EventQueue& instance()
  {
    static EventQueue event_queue;
    return event_queue;
  }

  inline void run(v8::Isolate* isolate, std::function<void()> user_func, uv_loop_t* loop = uv_default_loop())
  {
    run_func_(loop, [this, isolate, user_func]()
    {
      v8::HandleScope handle_scope(isolate);
      user_func();
      cleanup();
    });
  }

  template<typename T>
  T run(v8::Isolate* isolate, std::function<T()> user_func, uv_loop_t* loop = uv_default_loop())
  {
    std::unique_ptr<T> result;

    run_func_(loop, [this, isolate, user_func, &result]()
    {
      v8::HandleScope handle_scope(isolate);
      result = std::unique_ptr<T>(new T(std::move(user_func())));
      cleanup();
    });

    return std::move(*result);
  }

private:
  EventQueue() = default;
  EventQueue(EventQueue const&) = delete;
  EventQueue& operator=(EventQueue const&) = delete;

  inline void run_func_(uv_loop_t* loop, std::function<void()> task_func)
  {
    std::unique_lock<std::mutex> lock(mutex_);
    task_complete_ = false;

    uv_async_init(loop, &task_,
                  [](uv_async_t* handle)
    {
      std::function<void()> task_func_ = *((std::function<void()>*)handle->data);
      task_func_();
    });

    task_func_ = task_func;
    task_.data = &task_func_;

    uv_async_send(&task_);

    cond_.wait(lock, [this] { return task_complete_; });
  }

  inline void cleanup()
  {
    std::lock_guard<std::mutex> lock(mutex_);
    task_.data = this;
    uv_close((uv_handle_t*) &task_, [](uv_handle_t* handle)
    {
      EventQueue* thiz = (EventQueue*)handle->data;
      thiz->task_complete_ = true;
      thiz->cond_.notify_one();
    });
  }

  uv_async_t task_;
  std::function<void()> task_func_;

  bool task_complete_ = true;
  std::mutex mutex_;
  std::condition_variable cond_;
};

#endif // _UNITY_JS_EVENT_QUEUE_H_
