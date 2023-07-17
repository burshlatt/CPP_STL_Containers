#ifndef SRC_VECTOR_S21_VECTOR_H
#define SRC_VECTOR_S21_VECTOR_H

#include <algorithm>
#include <climits>
#include <cstdarg>
#include <initializer_list>
#include <iostream>
#include <limits>

namespace s21 {
template <class T>
class vector {
 public:
  using value_type = T;
  using iterator = T *;
  using reference = T &;
  using size_type = size_t;
  using const_iterator = const T *;
  using const_reference = const T &;

  vector() : size_(0U), capacity_(0U), array_(nullptr) {}

  vector(const vector &other) {
    size_ = other.size_;
    capacity_ = other.capacity_;
    array_ = new value_type[other.capacity_]{};
    std::copy_n(other.array_, other.size_, array_);
  }

  vector(vector &&other) noexcept {
    size_ = std::exchange(other.size_, 0);
    capacity_ = std::exchange(other.capacity_, 0);
    array_ = std::exchange(other.array_, nullptr);
  }

  explicit vector(const size_type size) {
    if ((int)size < 0) {
      throw std::out_of_range("Размер контейнера не должен быть меньше 0.");
    }
    size_ = size;
    capacity_ = size;
    array_ = size ? new value_type[size]{} : nullptr;
  }

  vector(std::initializer_list<value_type> const &items) {
    array_ = new value_type[items.size()]{};
    int i = 0;
    for (auto it = items.begin(); it != items.end(); it++) {
      array_[i] = *it;
      i++;
    }
    size_ = items.size();
    capacity_ = items.size();
  }

  ~vector() {
    if (array_ != nullptr) {
      size_ = 0;
      capacity_ = 0;
      delete[] array_;
      array_ = nullptr;
    }
  }

  iterator end() const {
    if (this->size_ < 1) {
      throw std::out_of_range("Контейнер пуст.");
    }
    return array_ + size_;
  }

  iterator begin() const {
    if (this->size_ < 1) {
      throw std::out_of_range("Контейнер пуст.");
    }
    return array_;
  }

  iterator data() const noexcept { return array_; }

  iterator insert(const_iterator index, const_reference value) {
    if (index > end()) {
      throw std::out_of_range("Выход за пределы контейнера.");
    }
    vector buffer(size_ + 1);
    int i = 0;
    for (auto it = begin(); it != index; it++) {
      buffer.array_[i++] = *it;
    }
    const int move = i;
    buffer.array_[i++] = value;
    for (auto it = index; it != end(); it++) {
      buffer.array_[i++] = *it;
    }
    delete[] array_;
    size_ = std::exchange(buffer.size_, 0);
    capacity_ = std::exchange(buffer.capacity_, 0);
    array_ = std::exchange(buffer.array_, nullptr);
    return array_ + move;
  }

  const_reference back() const {
    if (this->size_ < 1) {
      throw std::out_of_range("Контейнер пуст.");
    }
    return *(array_ + size_ - 1);
  }

  const_reference front() const {
    if (this->size_ < 1) {
      throw std::out_of_range("Контейнер пуст.");
    }
    return *array_;
  }

  bool empty() const noexcept { return size_ ? false : true; }

  size_type size() const noexcept { return size_; }

  size_type max_size() const noexcept {
    return std::numeric_limits<ptrdiff_t>::max() / sizeof(T);
  }

  size_type capacity() const noexcept { return capacity_; }

  value_type at(const size_type index) const {
    if (index >= size_) {
      throw std::out_of_range("Индекс находится вне границ контейнера.");
    }
    return array_[index];
  }

  vector &operator=(const vector &other) noexcept {
    this->~vector();
    size_ = other.size_;
    capacity_ = other.capacity_;
    if (capacity_) {
      array_ = new value_type[capacity_]{};
      std::copy_n(other.array_, other.size_, array_);
    } else {
      array_ = nullptr;
    }
    return *this;
  }

  reference operator[](const size_type index) const noexcept {
    return array_[index];
  }

  void clear() noexcept { size_ = 0; }

  void pop_back() noexcept {
    vector buffer(*this);
    delete[] array_;
    array_ = new value_type[size_ - 1]{};
    std::copy_n(buffer.array_, size_ - 1, array_);
    size_--;
  }

  void shrink_to_fit() noexcept {
    vector buffer(*this);
    delete[] array_;
    array_ = new value_type[size_]{};
    std::copy_n(buffer.array_, size_, array_);
    capacity_ = size_;
  }

  void erase(const_iterator index) {
    if (index > end()) {
      throw std::out_of_range("Выход за пределы контейнера.");
    }
    vector buffer(size_ - 1);
    int i = 0;
    for (auto it = begin(); it != index; it++) {
      buffer.array_[i++] = *it;
    }
    for (auto it = index + 1; it != end(); it++) {
      buffer.array_[i++] = *it;
    }
    delete[] array_;
    size_ = std::exchange(buffer.size_, 0);
    array_ = std::exchange(buffer.array_, nullptr);
  }

  void swap(vector &other) noexcept {
    size_ = std::exchange(other.size_, size_);
    capacity_ = std::exchange(other.capacity_, capacity_);
    array_ = std::exchange(other.array_, array_);
  }

  void reserve(const size_type size) noexcept {
    if (size > capacity_) {
      vector buffer(*this);
      delete[] array_;
      array_ = new value_type[size]{};
      std::copy_n(buffer.array_, size_, array_);
      capacity_ = size;
    }
  }

  void push_back(const_reference value) noexcept {
    if (size_ == capacity_) {
      reserve(size_ * 2);
    }
    array_[size_++] = value;
  }

 private:
  size_type size_;
  size_type capacity_;
  value_type *array_;
};
}  // namespace s21

#endif  // SRC_VECTOR_S21_VECTOR_H
