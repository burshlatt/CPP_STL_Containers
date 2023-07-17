#ifndef SRC_STACK_S21_STACK_H
#define SRC_STACK_S21_STACK_H

#include <algorithm>
#include <initializer_list>
#include <iostream>

namespace s21 {
template <class T>
class stack {
 public:
  using value_type = T;
  using reference = T &;
  using size_type = size_t;
  using const_reference = const T &;

  stack() : size_(0U), capacity_(0U), array_(nullptr) {}

  stack(const stack &other) {
    size_ = other.size_;
    capacity_ = other.capacity_;
    array_ = new value_type[other.capacity_]{};
    std::copy_n(other.array_, other.size_, array_);
  }

  stack(stack &&other) noexcept {
    size_ = std::exchange(other.size_, 0);
    capacity_ = std::exchange(other.capacity_, 0);
    array_ = std::exchange(other.array_, nullptr);
  }

  stack(std::initializer_list<value_type> const &items) {
    array_ = new value_type[items.size()]{};
    int i = 0;
    for (auto it = items.begin(); it != items.end(); it++) {
      array_[i] = *it;
      i++;
    }
    size_ = items.size();
    capacity_ = items.size();
  }

  ~stack() {
    if (array_ != nullptr) {
      size_ = 0;
      capacity_ = 0;
      delete[] array_;
      array_ = nullptr;
    }
  }

  const_reference top() const {
    if (!size_) {
      throw std::out_of_range("Стек пуст.");
    }
    return *(array_ + size_ - 1);
  }

  size_type size() const noexcept { return size_; }

  void pop() {
    if (!size_) {
      throw std::out_of_range("Стек пуст.");
    }
    stack buffer(*this);
    delete[] array_;
    size_--;
    array_ = new value_type[size_]{};
    std::copy_n(buffer.array_, size_, array_);
  }

  bool empty() const noexcept { return size_ ? false : true; }

  void swap(stack &other) noexcept {
    size_ = std::exchange(other.size_, size_);
    capacity_ = std::exchange(other.capacity_, size_);
    array_ = std::exchange(other.array_, array_);
  }

  void push(const_reference value) noexcept {
    if (size_ == capacity_) {
      stack buffer(*this);
      delete[] array_;
      capacity_ += 10;
      array_ = new value_type[capacity_]{};
      std::copy_n(buffer.array_, size_, array_);
    }
    array_[size_++] = value;
  }

  stack &operator=(const stack &other) noexcept {
    this->~stack();
    size_ = other.size_;
    capacity_ = other.capacity_;
    if (capacity_) {
      array_ = new value_type[size_]{};
      std::copy_n(other.array_, other.size_, array_);
    } else {
      array_ = nullptr;
    }
    return *this;
  }

 private:
  size_type size_;
  size_type capacity_;
  value_type *array_;
};
}  // namespace s21

#endif  // SRC_STACK_S21_STACK_H
