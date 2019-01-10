#pragma once

#include "BArray.h"
#include "OList.h"
#include <stddef.h>

constexpr int DefaultMaxPriorities = 10;

template<typename T>
class Queue : public OList<T>
{
  public:
    using base = OList<T>;

    Queue() : base() {}
    ~Queue() { base::destroy(); }

    void enqueue(T item)
    {
        base::insert(item);
    }

    T dequeue()
    {
        T tmp = base::tail();
        base::pop_tail();
        return tmp;
    }
};

template<typename T>
class PriorityQueue
{
  public:
    using queue_t = Queue<T>;
    using queue_ptr = queue_t*;
    using pqueue_t = BArray<queue_ptr>;

    explicit PriorityQueue(int max_priorities = DefaultMaxPriorities)
      : size_(0)
      , highest_(0)
      , queue_(max_priorities+1)
    {}

    ~PriorityQueue()
    {
        for (int i = 0; i < queue_.size(); ++i) {
            queue_ptr q = queue_.get(i);
            delete q;
        }
    }

    void enqueue(int priority, T item)
    {
        if (priority >= queue_.size()) {
            queue_.add(priority, nullptr);
        }
        if (priority >= 0 && priority < queue_.size()) {
            queue_ptr q = queue_.get(priority);
            if (q == nullptr) {
                q = new queue_t;
                queue_.set(priority, q);
            }
            q->enqueue(item);
            size_++;
            highest_ = std::max(highest_, priority);
        }
    }

    T dequeue()
    {
        if (size_ == 0) {
            return T();
        }

        queue_ptr q = highest_queue();
        if (q == nullptr || q->size() == 0) {
            return T();
        }

        size_--;
        return q->dequeue();
    }

    size_t size() { return size_; }
    size_t highest() { return highest_; }

  private:
    int size_;
    int highest_;
    pqueue_t queue_;

    queue_ptr highest_queue()
    {
        for (int i = highest_; i >= 0; --i) {
            queue_ptr q = queue_.get(i);
            if (q != nullptr && q->size() > 0) {
                return q;
            }
        }
        return nullptr;
    }

};
