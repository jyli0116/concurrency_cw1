#ifndef HASH_SET_REFINABLE_H
#define HASH_SET_REFINABLE_H

#include <stdio.h>

#include <cassert>
#include <cstddef>
#include <functional>
#include <mutex>
#include <shared_mutex>
#include <vector>

#include "src/hash_set_base.h"

template <typename T>
class HashSetRefinable : public HashSetBase<T> {
 public:
  explicit HashSetRefinable(size_t initial_capacity)
      : current_capacity_(initial_capacity), set_size_(0), {
    table_.reserve(initial_capacity);
    std::unique_lock<std::shared_mutex> resize_lock(resize_mutex_);
    mutexes_ = std::vector<std::mutex>(current_capacity_);
    for (size_t i = 0; i < current_capacity_; i++) {
      table_.push_back(std::vector<T>());
    }
  }

  bool Add(T elem) final {
    std::shared_lock<std::shared_mutex> resize_lock(resize_mutex_);
    std::unique_lock<std::mutex> lock(
        mutexes_[std::hash<T>()(elem) % current_capacity_]);

    std::vector<T>& bucket_ =
        table_.at(std::hash<T>()(elem) % current_capacity_);

    // check if element is already present in bucket
    auto bucket_elem_ = bucket_.begin();
    while (bucket_elem_ != bucket_.end()) {
      if (*bucket_elem_ == elem) {
        return false;
      }
      ++bucket_elem_;
    }

    // if not add to bucket
    set_size_++;
    bucket_.push_back(elem);

    if (Policy()) {
      // resize needs all threads unlocked prior to calling it
      resize_lock.unlock();
      lock.unlock();
      Resize();
    }
    return true;
  }

  bool Remove(T elem) final {
    std::shared_lock<std::shared_mutex> resize_lock(resize_mutex_);

    // since dont need ot unlock this early, could also use scoped_lock?
    // mutexes_[std::hash<T>()(elem) % initial_capacity_].lock();
    std::scoped_lock<std::mutex> scoped_lock(
        mutexes_[std::hash<T>()(elem) % current_capacity_]);

    if (set_size_.load() == 0) {
      return false;
    }

    std::vector<T>& bucket_ =
        table_.at(std::hash<T>()(elem) % current_capacity_);

    // check if element is already present in bucket if so, remove from
    auto bucket_elem_ = bucket_.begin();
    while (bucket_elem_ != bucket_.end()) {
      if (*bucket_elem_ == elem) {
        bucket_.erase(bucket_elem_);
        set_size_--;
        return true;
      }
      ++bucket_elem_;
    }
    return false;
  }

  [[nodiscard]] bool Contains(T elem) final {
    std::shared_lock<std::shared_mutex> resize_lock(resize_mutex_);
    std::scoped_lock<std::mutex> scoped_lock(
        mutexes_[std::hash<T>()(elem) % current_capacity_]);

    std::vector<T>& bucket_ =
        table_.at(std::hash<T>()(elem) % current_capacity_);
    return std::find(bucket_.begin(), bucket_.end(), elem) != bucket_.end();
  }

  [[nodiscard]] size_t Size() const final { return set_size_.load(); }

 private:
  bool Policy() { return set_size_.load() / current_capacity_ > 4; }

  void Resize() {
    size_t old_capacity = current_capacity_;
    // Block other operations while resizing
    std::lock_guard<std::shared_mutex> resize_lock(resize_mutex_);
    for (std::mutex& mutex : mutexes_) {
      std::scoped_lock<std::mutex> lock(mutex);
    }

    // check if another thread already resized
    if (old_capacity != current_capacity_) {
      return;
    }

    size_t new_capacity = 2 * old_capacity;
    current_capacity_.store(new_capacity);

    std::vector<std::vector<T>> old_table_ = table_;
    table_ = std::vector<std::vector<T>>(new_capacity);
    for (std::vector<T> bucket : old_table_) {
      for (T elem : bucket) {
        std::vector<T>& curr_bucket_ =
            table_.at(std::hash<T>()(elem) % new_capacity);
        curr_bucket_.push_back(elem);
      }
    }

    // new mutexes
    mutexes_ = std::vector<std::mutex>(new_capacity);

    //   current_capacity_ = new_capacity_;
  }

  // size_t const initial_capacity_;
  std::atomic<size_t> current_capacity_;
  std::vector<std::vector<T>> table_;
  std::vector<std::mutex> mutexes_;
  std::atomic<size_t> set_size_;
  // wrap in unique lock for resize, wrap in shared lock for read
  std::shared_mutex resize_mutex_;  // Mutex to protect resizing
};

#endif  // HASH_SET_REFINABLE_H
