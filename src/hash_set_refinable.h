#ifndef HASH_SET_REFINABLE_H
#define HASH_SET_REFINABLE_H

#include <stdio.h>

#include <atomic>
#include <cassert>
#include <cstddef>
#include <functional>
#include <mutex>
#include <shared_mutex>
#include <vector>

#include "src/hash_set_base.h"

/*
  similar to how mark and owner is used in the book, we use a shared mutex for
  managing resizing and exclusive mutex for each bucket. By using a shared lock
  for Add/Remove/Contain and exclusive lock for resizing, we ensure that no
  other thread is modifying any bucket while resizing is in progress and still
  allow multiple readers to access the hashset when resizing is not in progress.
*/

template <typename T>
class HashSetRefinable : public HashSetBase<T> {
 public:
  explicit HashSetRefinable(size_t initial_capacity)
      : current_capacity_(initial_capacity), set_size_(0) {
    table_.reserve(initial_capacity);
    mutexes_ = std::vector<std::mutex>(initial_capacity);
    for (size_t i = 0; i < current_capacity_; i++) {
      table_.push_back(std::vector<T>());
    }
  }

  bool Add(T elem) final {
    // shared lock allows multiple readers and prevents concurrent resizing
    std::shared_lock<std::shared_mutex> resize_lock(resize_mutex_);
    std::unique_lock<std::mutex> lock(
        mutexes_[std::hash<T>()(elem) % current_capacity_]);

    std::vector<T>& bucket_ =
        table_.at(std::hash<T>()(elem) % current_capacity_);

    // check if element is already present in bucket, add if not
    auto bucket_elem_ = bucket_.begin();
    while (bucket_elem_ != bucket_.end()) {
      if (*bucket_elem_ == elem) {
        return false;
      }
      ++bucket_elem_;
    }
    set_size_++;
    bucket_.push_back(elem);

    // check if resizing is needed based on load factor
    if (Policy()) {
      // unlock before resizing to avoid deadlock
      resize_lock.unlock();
      lock.unlock();
      Resize();
    }
    return true;
  }

  bool Remove(T elem) final {
    // reader lock for resizing
    std::shared_lock<std::shared_mutex> resize_lock(resize_mutex_);
    std::scoped_lock<std::mutex> lock(
        mutexes_[std::hash<T>()(elem) % current_capacity_]);

    if (set_size_.load() == 0) {
      return false;
    }

    std::vector<T>& bucket_ =
        table_.at(std::hash<T>()(elem) % current_capacity_);

    // check if element is already present in bucket, remove if so
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
    // reader lock for resizing
    std::shared_lock<std::shared_mutex> resize_lock(resize_mutex_);
    std::scoped_lock<std::mutex> lock(
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

    // lightweight guard for automatic unlock
    // exclusive writer lock for resizing
    std::lock_guard<std::shared_mutex> resize_lock(resize_mutex_);

    // ensure no other thread is modifying any bucket
    for (std::mutex& mutex : mutexes_) {
      std::scoped_lock<std::mutex> lock(mutex);
    }

    // verify no other resize operation has been performed
    if (old_capacity != current_capacity_) {
      return;
    }

    size_t new_capacity = 2 * old_capacity;
    current_capacity_.store(new_capacity);

    // rehash and redistribute table elements
    std::vector<std::vector<T>> old_table_ = table_;
    table_ = std::vector<std::vector<T>>(new_capacity);
    for (std::vector<T> bucket : old_table_) {
      for (T elem : bucket) {
        std::vector<T>& curr_bucket_ =
            table_.at(std::hash<T>()(elem) % new_capacity);
        curr_bucket_.push_back(elem);
      }
    }

    // reinitialize mutexes for new capacity
    mutexes_ = std::vector<std::mutex>(new_capacity);
  }

  std::atomic<size_t> current_capacity_;
  std::vector<std::vector<T>> table_;
  std::vector<std::mutex> mutexes_;
  std::atomic<size_t> set_size_;
  // allow multiple readers and only one writer for resize
  std::shared_mutex resize_mutex_;
};

#endif  // HASH_SET_REFINABLE_H
