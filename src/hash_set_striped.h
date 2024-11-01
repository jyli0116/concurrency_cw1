#ifndef HASH_SET_STRIPED_H
#define HASH_SET_STRIPED_H

#include <stdio.h>

#include <cassert>
#include <cstddef>
#include <functional>
#include <mutex>
#include <vector>

#include "src/hash_set_base.h"

/*
following the book's guidance
we equipped each public function (except for Add) with a scoped lock 
which will lock itself at function entry point and automatically unlock at exit points 
by using this, we ensure the synchronisation of the entire public function
*/

template <typename T>
class HashSetStriped : public HashSetBase<T> {
 public:
  explicit HashSetStriped(size_t initial_capacity)
      : initial_capacity_(initial_capacity),
        current_capacity_(initial_capacity) {
    table_.reserve(initial_capacity);
    set_size_.store(0);
    mutexes_ = new std::mutex[initial_capacity];
    for (size_t i = 0; i < initial_capacity; i++) {
      table_.push_back(std::vector<T>());
    }
  }

  /*
  we used mutex lock and unlock functions in Add instead of a scoped lock
  it is to unlock all mutexes before resizing, whereas a scoped lock can only unlock at exit points
  */
  bool Add(T elem) final {
    mutexes_[std::hash<T>()(elem) % initial_capacity_].lock();

    std::vector<T>& bucket_ =
        table_.at(std::hash<T>()(elem) % current_capacity_);

    // check if element is already present in bucket
    auto bucket_elem_ = bucket_.begin();
    while (bucket_elem_ != bucket_.end()) {
      if (*bucket_elem_ == elem) {
        mutexes_[std::hash<T>()(elem) % initial_capacity_].unlock();
        return false;
      }
      ++bucket_elem_;
    }

    // if not add to bucket
    set_size_++;
    bucket_.push_back(elem);

    // resize needs all threads unlocked prior to calling it
    mutexes_[std::hash<T>()(elem) % initial_capacity_].unlock();

    if (Policy()) {
      Resize();
    }

    return true;
  }

  bool Remove(T elem) final {
    // since dont need ot unlock this early, could also use scoped_lock?
    std::scoped_lock<std::mutex> scoped_lock(
        mutexes_[std::hash<T>()(elem) % initial_capacity_]);

    if (set_size_.load() == 0) {
      return false;
    }

    std::vector<T>& bucket_ =
        table_.at(std::hash<T>()(elem) % current_capacity_);

    // check if element is already present in bucket if so, remove from bucket
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
    std::scoped_lock<std::mutex> scoped_lock(
        mutexes_[std::hash<T>()(elem) % initial_capacity_]);

    std::vector<T>& bucket_ =
        table_.at(std::hash<T>()(elem) % current_capacity_);

    return std::find(bucket_.begin(), bucket_.end(), elem) != bucket_.end();
  }

  [[nodiscard]] size_t Size() const final { return set_size_.load(); }

 private:
  bool Policy() { return set_size_.load() / current_capacity_ > 4; }

  void Resize() {
    size_t oldCapacity = current_capacity_.load();
    // lock all mutexes
    for (size_t i = 0; i < initial_capacity_; i++) {
      mutexes_[i].lock();
    }
    if (oldCapacity == current_capacity_.load()) {
      current_capacity_.store(current_capacity_.load() * 2);

      std::vector<std::vector<T>> old_table_ = table_;
      table_ = std::vector<std::vector<T>>(current_capacity_);
      for (std::vector<T> bucket : old_table_) {
        for (T elem : bucket) {
          std::vector<T>& curr_bucket_ =
              table_.at(std::hash<T>()(elem) % current_capacity_);
          curr_bucket_.push_back(elem);
        }
      }
    }

    for (size_t i = 0; i < initial_capacity_; i++) {
      mutexes_[i].unlock();
    }
  }

  /*
  we use atomic integer value for hashset capacity and size of buckets
  it is to ensure no race condition when assigning and modifying their values
  */
  size_t const initial_capacity_;
  std::atomic<size_t> current_capacity_;
  std::vector<std::vector<T>> table_;
  //follows the book's guidance 
  std::mutex* mutexes_;
  std::atomic<size_t> set_size_;
};

#endif  // HASH_SET_STRIPED_H
