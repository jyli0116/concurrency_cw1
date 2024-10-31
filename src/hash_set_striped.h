#ifndef HASH_SET_STRIPED_H
#define HASH_SET_STRIPED_H

#include <stdio.h>

#include <cassert>
#include <cstddef>
#include <vector>
#include <functional>
#include <mutex>

#include "src/hash_set_base.h"

template <typename T>
class HashSetStriped : public HashSetBase<T> {
  public:
    explicit HashSetStriped(size_t initial_capacity) : initial_capacity_(initial_capacity), current_capacity_(initial_capacity) {
      table_.reserve(initial_capacity);
      set_size_.store(0);
      mutexes_ = new std::mutex[initial_capacity];
      for (size_t i = 0; i < initial_capacity; i++) {
        table_.push_back(std::vector<T>());
      }
    }


    bool Add(T elem) final {
      mutexes_[std::hash<T>()(elem) % initial_capacity_].lock();
      
      std::vector<T>& bucket_ = table_.at(std::hash<T>()(elem) % current_capacity_);

      // check if element is already present in bucket
      auto bucket_elem_ = bucket_.begin();
      while (bucket_elem_ != bucket_.end()) {
        if(*bucket_elem_ == elem) {
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
      //mutexes_[std::hash<T>()(elem) % initial_capacity_].lock();
      std::scoped_lock<std::mutex> scoped_lock(mutexes_[std::hash<T>()(elem) % initial_capacity_]);

      if (set_size_.load() == 0) {
        return false;
      }

      std::vector<T>& bucket_ = table_.at(std::hash<T>()(elem) % current_capacity_);

      // check if element is already present in bucket if so, remove from bucket
      auto bucket_elem_ = bucket_.begin();
      while (bucket_elem_ != bucket_.end()) {
        if(*bucket_elem_ == elem) {
          bucket_.erase(bucket_elem_);
          set_size_--;
          return true;
        }
        ++bucket_elem_;
      }
      return false;
    }

    [[nodiscard]] bool Contains(T elem) final {
      std::scoped_lock<std::mutex> scoped_lock(mutexes_[std::hash<T>()(elem) % initial_capacity_]);

      std::vector<T>& bucket_ = table_.at(std::hash<T>()(elem) % current_capacity_);
      
      return std::find(bucket_.begin(), bucket_.end(), elem) != bucket_.end();
    }

    [[nodiscard]] size_t Size() const final {
      return set_size_.load();
    }

  private: 
    bool Policy() {
      return set_size_.load() / current_capacity_ > 4;
    }

    void Resize() {
      // lock all mutexes
      for (size_t i = 0; i < initial_capacity_; i++) {
        mutexes_[i].lock();
      }
      
      // TODO: shorten down to one instruction
      size_t new_capacity_ = current_capacity_ * 2;
      current_capacity_ = new_capacity_;

      std::vector<std::vector<T>> old_table_ = table_;
      table_ = std::vector<std::vector<T>>(new_capacity_);
      for (std::vector<T> bucket : old_table_) {
        for (T elem : bucket) {
          std::vector<T>& curr_bucket_ = table_.at(std::hash<T>()(elem) % new_capacity_);
          curr_bucket_.push_back(elem);
        }
      }

      for (size_t i = 0; i < initial_capacity_; i++) {
        mutexes_[i].unlock();
      }
    }

    size_t const initial_capacity_;
    std::atomic<size_t> current_capacity_;
    std::vector<std::vector<T>> table_;
    std::mutex* mutexes_;
    std::atomic<size_t> set_size_;
};

#endif  // HASH_SET_STRIPED_H
