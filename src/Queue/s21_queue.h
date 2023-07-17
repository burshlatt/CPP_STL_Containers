#ifndef SRC_QUEUE_S21_QUEUE_H
#define SRC_QUEUE_S21_QUEUE_H

#include <iostream>
#include <utility>

namespace s21 {
template <class T>
class queue {
 public:
  using value_type = T;
  using reference = T &;
  using size_type = size_t;
  using const_reference = const T &;

  queue() : head_(nullptr), tail_(nullptr), size_(0U) {}

  queue(const queue &other) {
    head_ = nullptr;
    tail_ = nullptr;
    size_ = 0U;
    if (!other.empty()) {
      node *buffer_ = other.head_;
      for (size_t i = 0; i < other.size_; i++) {
        push(buffer_->value_);
        buffer_ = buffer_->next_;
      }
      buffer_ = nullptr;
    }
  }

  queue(queue &&other) noexcept {
    head_ = std::exchange(other.head_, nullptr);
    tail_ = std::exchange(other.tail_, nullptr);
    size_ = std::exchange(other.size_, 0U);
  }

  queue(std::initializer_list<value_type> const &items) {
    head_ = nullptr;
    tail_ = nullptr;
    size_ = 0U;
    for (auto it = items.begin(); it != items.end(); it++) {
      push(*it);
    }
  }

  ~queue() {
    while (!empty()) {
      pop();
    }
    head_ = nullptr;
    tail_ = nullptr;
    size_ = 0U;
  }

  queue &operator=(const queue &other) {
    this->~queue();
    if (!other.empty()) {
      node *buffer_ = other.head_;
      for (size_t i = 0; i < other.size_; i++) {
        push(buffer_->value_);
        buffer_ = buffer_->next_;
      }
      buffer_ = nullptr;
    } else {
      head_ = nullptr;
      tail_ = nullptr;
      size_ = 0U;
    }
    return *this;
  }

  queue &operator=(queue &&other) {
    this->~queue();
    size_ = std::exchange(other.size_, 0);
    head_ = std::exchange(other.head_, nullptr);
    tail_ = std::exchange(other.tail_, nullptr);
    return *this;
  }

  const_reference back() const {
    if (empty()) {
      throw std::out_of_range("Контейнер пуст.");
    }
    return tail_->value_;
  }

  const_reference front() const {
    if (empty()) {
      throw std::out_of_range("Контейнер пуст.");
    }
    return head_->value_;
  }

  size_type size() const noexcept { return size_; }

  void pop() {
    if (empty()) {
      throw std::out_of_range("Контейнер пуст.");
    }
    node *buffer_ = head_->next_;
    delete[] head_;
    head_ = buffer_;
    size_--;
  }

  bool empty() const noexcept { return size_ ? false : true; }

  void swap(queue &other) noexcept {
    head_ = std::exchange(other.head_, head_);
    tail_ = std::exchange(other.tail_, tail_);
    size_ = std::exchange(other.size_, size_);
  }

  void push(const_reference value) noexcept {
    node *buffer_ = new node(value);
    if (empty()) {
      head_ = tail_ = buffer_;
    } else {
      tail_->next_ = buffer_;
      tail_ = buffer_;
    }
    size_++;
  }

 private:
  struct node {
    node *next_;
    value_type value_;
    node(const_reference value) : next_(nullptr), value_(value) {}
  };
  node *head_;
  node *tail_;
  size_type size_;
};
}  // namespace s21

#endif  // SRC_QUEUE_S21_QUEUE_H
