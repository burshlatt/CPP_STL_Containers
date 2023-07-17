#ifndef SRC_MAP_S21_ITERATOR_H
#define SRC_MAP_S21_ITERATOR_H

#include <algorithm>
#include <iostream>

namespace s21 {
template <typename T>
struct TreeNode {
  using value_type = T;
  value_type value_{};
  TreeNode *parent_{};
  TreeNode *left_{};
  TreeNode *right_{};

  explicit TreeNode(value_type value)
      : value_(value), parent_(nullptr), left_(nullptr), right_(nullptr) {}

  TreeNode(TreeNode *parent, value_type value)
      : value_(value), parent_(parent), left_(nullptr), right_(nullptr) {}

  TreeNode(const TreeNode parent, value_type value)
      : value_(value), parent_(parent), left_(nullptr), right_(nullptr) {}
};

template <typename IteratorType, typename T>
class BaseTreeIterator {
 public:
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;

  BaseTreeIterator() : current_(nullptr){};

  BaseTreeIterator(TreeNode<value_type> *node) : current_(node){};

  BaseTreeIterator(const BaseTreeIterator &other) : current_(other.current_) {}

  BaseTreeIterator(BaseTreeIterator &&other) noexcept
      : current_(other.current_) {}

  BaseTreeIterator &operator=(const BaseTreeIterator &other) {
    if (other != this) {
      current_ = other.current_;
    }
    return *this;
  }

  BaseTreeIterator &operator=(BaseTreeIterator &&other) noexcept {
    current_ = other.current_;
    other.current_ = nullptr;
    return *this;
  }

  bool operator!=(const BaseTreeIterator &other) const {
    return current_ != other.current_;
  }

  bool operator==(const BaseTreeIterator &other) const {
    return current_ == other.current_;
  }

  IteratorType operator++() {
    if (this->current_ != nullptr) {
      if (this->current_->right_ != nullptr) {
        this->current_ = this->current_->right_;
        while (this->current_->left_ != nullptr)
          this->current_ = this->current_->left_;
      } else {
        while (this->current_->parent_ != nullptr &&
               this->current_ == this->current_->parent_->right_) {
          this->current_ = this->current_->parent_;
        }
        this->current_ = this->current_->parent_;
      }
    }
    return *static_cast<IteratorType *>(this);
  }

  IteratorType operator--() {
    if (this->current_ != nullptr) {
      if (this->current_->left_ != nullptr) {
        this->current_ = this->current_->left_;
        while (this->current_->right_ != nullptr) {
          this->current_ = this->current_->right_;
        }
      } else {
        while (this->current_->parent_ != nullptr &&
               this->current_ == this->current_->parent_->left_) {
          this->current_ = this->current_->parent_;
        }
        this->current_ = this->current_->parent_;
      }
    }
    return *static_cast<IteratorType *>(this);
  }

 protected:
  TreeNode<value_type> *current_{};
  template <typename Key, typename M>
  friend class map;
  template <typename Key>
  friend class set;
};

template <typename T>
class ConstIterator : public BaseTreeIterator<ConstIterator<T>, T> {
 public:
  using BaseTreeIterator<ConstIterator<T>, T>::BaseTreeIterator;
  const T &operator*() {
    if (this->current_) {
      return this->current_->value_;
    }
    static T default_value = T{};
    return default_value;
  }
};

template <typename T>
class Iterator : public BaseTreeIterator<Iterator<T>, T> {
 public:
  using BaseTreeIterator<Iterator<T>, T>::BaseTreeIterator;
  T &operator*() {
    if (this->current_) {
      return this->current_->value_;
    }
    static T default_value = T{};
    return default_value;
  }
  operator ConstIterator<T>() noexcept {
    return ConstIterator<T>(this->current_);
  }
};
}  // namespace s21
#endif  // SRC_MAP_S21_ITERATOR_H
