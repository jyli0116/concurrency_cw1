#ifndef HASH_SET_SEQUENTIAL_H
#define HASH_SET_SEQUENTIAL_H

#include <stdio.h>

#include <cassert>
#include <functional>
#include <vector>

#include "src/hash_set_base.h"

template <typename T>
class HashSetSequential : public HashSetBase<T> {
 public:
  explicit HashSetSequential(size_t initial_capacity)
      : initial_capacity_(initial_capacity), set_size_(0) {
    table_.reserve(initial_capacity);
    for (size_t i = 0; i < initial_capacity; i++) {
      table_.push_back(std::vector<T>());
    }
  }

  // Adds element to hashset
  bool Add(T elem) final {
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

  // Removes element from hashset
  bool Remove(T elem) final {
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

  // Check if item contains hashset
  [[nodiscard]] bool Contains(T elem) final {
    std::vector<T>& bucket_ =
        table_.at(std::hash<T>()(elem) % initial_capacity_);
    return std::find(bucket_.begin(), bucket_.end(), elem) != bucket_.end();
  }

  // Returns size of hashset
  [[nodiscard]] size_t Size() const final { return set_size_; }

 private:
  // Decides wherther to resize the set
  bool Policy() { return set_size_ / initial_capacity_ > 4; }

  // doubles the capacity of the table
  void Resize() {
    // TODO: shorten down to one instruction
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

  // used to represent the Hashset: a vector of vectors of type T: each vector
  // representing the bucket
  size_t initial_capacity_;
  size_t set_size_;
  // idk why my intellisense isn't recognising std here but
  std::vector<std::vector<T>> table_;
};

#endif  // HASH_SET_SEQUENTIAL_H
