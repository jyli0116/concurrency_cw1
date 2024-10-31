#ifndef HASH_SET_COARSE_GRAINED_H
#define HASH_SET_COARSE_GRAINED_H

#include <stdio.h>

#include <cassert>
#include <functional>
#include <vector>

#include "src/hash_set_base.h"

template <typename T>
class HashSetCoarseGrained : public HashSetBase<T> {
 public:
  explicit HashSetCoarseGrained(size_t initial_capacity)
      : initial_capacity_(initial_capacity), set_size_(0) {
    table_.reserve(initial_capacity);
    for (size_t i = 0; i < initial_capacity; i++) {
      table_.push_back(std::vector<T>());
    }
  }

  bool Add(T elem) final {
    std::scoped_lock<std::mutex> scoped_lock(mutex_);

    std::vector<T>& bucket_ =
        table_.at(std::hash<T>()(elem) % initial_capacity_);

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
      Resize();
    }

    return true;
  }

  bool Remove(T elem) final {
    std::scoped_lock<std::mutex> scoped_lock(mutex_);

    if (set_size_ == 0) {
      return false;
    }

    std::vector<T>& bucket_ =
        table_.at(std::hash<T>()(elem) % initial_capacity_);

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
    std::scoped_lock<std::mutex> scoped_lock(mutex_);

    std::vector<T>& bucket_ =
        table_.at(std::hash<T>()(elem) % initial_capacity_);
    return std::find(bucket_.begin(), bucket_.end(), elem) != bucket_.end();
  }

  [[nodiscard]] size_t Size() const final { return set_size_.load(); }

 private:
  // Decides wherther to resize the set
  bool Policy() { return set_size_ / initial_capacity_ > 4; }

  void Resize() {
    initial_capacity_ *= 2;

    std::vector<std::vector<T>> old_table_ = table_;
    table_ = std::vector<std::vector<T>>(initial_capacity_);
    for (std::vector<T> bucket : old_table_) {
      for (T elem : bucket) {
        std::vector<T>& curr_bucket_ =
            table_.at(std::hash<T>()(elem) % initial_capacity_);
        curr_bucket_.push_back(elem);
      }
    }
  }

  size_t initial_capacity_;
  std::atomic<size_t> set_size_;
  std::vector<std::vector<T>> table_;
  std::mutex mutex_;
};

#endif  // HASH_SET_COARSE_GRAINED_H
