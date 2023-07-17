#ifndef SRC_ARRAY_S21_ARRAY_H
#define SRC_ARRAY_S21_ARRAY_H

#include <algorithm>
#include <initializer_list>
#include <iostream>

namespace s21 {
template <class T, size_t N>
class array {
 public:
  using iterator = T *;
  using value_type = T;
  using reference = T &;
  using size_type = size_t;
  using const_iterator = const T *;
  using const_reference = const T &;

  array() {}

  array(const array &other) { std::copy_n(other.array_, size_, array_); }

  array(array &&other) noexcept {
    std::move(other.begin(), other.end(), array_);
    other.size_ = 0;
  }

  array(std::initializer_list<value_type> const &items) {
    if (items.size() != N) {
      throw std::out_of_range(
          "Количество элементов должно быть равно размеру массива.");
    }
    int i = 0;
    for (auto it = items.begin(); it != items.end(); it++) {
      array_[i] = *it;
      i++;
    }
  }

  ~array() {
    fill(0);
    size_ = 0;
  }

  reference operator[](size_type index) noexcept { return array_[index]; }

  array &operator=(const array &other) noexcept {
    this->~array();
    std::copy_n(other.array_, other.size_, array_);
    return *this;
  }

  array &operator=(array &&other) noexcept {
    this->~array();
    size_ = std::exchange(other.size_, 0);
    std::swap(array_, other.array_);
    return *this;
  }

  iterator begin() {
    if (size_ < 1) {
      throw std::out_of_range("Контейнер пуст.");
    }
    return array_;
  }

  iterator end() {
    if (size_ < 1) {
      throw std::out_of_range("Контейнер пуст.");
    }
    return array_ + size_;
  }

  iterator data() noexcept { return array_; }

  size_type size() const noexcept { return size_; }

  size_type max_size() const noexcept { return N; }

  const_reference back() const {
    if (size_ < 1) {
      throw std::out_of_range("Контейнер пуст.");
    }
    return *(array_ + size_ - 1);
  }

  const_reference front() const {
    if (size_ < 1) {
      throw std::out_of_range("Контейнер пуст.");
    }
    return *array_;
  }

  reference at(size_type index) {
    if (index >= size_) {
      throw std::out_of_range("Индекс находится вне границ контейнера.");
    }
    return array_[index];
  }

  bool empty() const noexcept { return size_ ? false : true; }

  void swap(array &other) noexcept {
    for (size_t i = 0; i < size_; i++) {
      array_[i] = std::exchange(other.array_[i], array_[i]);
    }
  }

  void fill(const_reference value) noexcept {
    for (size_t i = 0; i < size_; i++) {
      array_[i] = value;
    }
  }

 private:
  size_type size_ = N;
  value_type array_[N + 1]{};
};
}  // namespace s21

#endif  // SRC_ARRAY_S21_ARRAY_H
