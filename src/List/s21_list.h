#ifndef CPP2_S21_CONTAINERS_1_SRC_S21_LIST_H
#define CPP2_S21_CONTAINERS_1_SRC_S21_LIST_H

#include <iostream>

namespace s21 {

template <typename Type>
class Node {
 private:
  template <typename IteratorType, typename NodeType>
  friend class BaseIterator;
  template <typename NodeType>
  friend class list;
  template <typename NodeType>
  friend class ListConstIterator;
  template <typename NodeType>
  friend class ListIterator;
  Node(Type value) : node_value_(value) {}
  ~Node() = default;

  Type node_value_;
  Node<Type> *prev_node_;
  Node<Type> *next_node_;
};

template <class IteratorType, typename NodeType>
class BaseIterator {
 public:
  BaseIterator(Node<NodeType> *node_ptr = nullptr) : current_node_(node_ptr){};
  BaseIterator(const IteratorType &iterator)
      : IteratorType(iterator->current_node_){};
  BaseIterator() = default;

  bool operator==(IteratorType const &other) const noexcept {
    return (current_node_ == other.current_node_);
  };
  bool operator!=(IteratorType const &other) const noexcept {
    return (current_node_ != other.current_node_);
  };
  IteratorType &operator++() {
    current_node_ = current_node_->next_node_;
    return *static_cast<IteratorType *>(this);
  };
  IteratorType &operator--() {
    current_node_ = current_node_->prev_node_;
    return *static_cast<IteratorType *>(this);
  };

 protected:
  Node<NodeType> *current_node_;
};

template <typename Type>
class ListConstIterator : public BaseIterator<ListConstIterator<Type>, Type> {
 public:
  using BaseIterator<ListConstIterator, Type>::BaseIterator;
  const Type &operator*() { return this->current_node_->node_value_; };

 protected:
  template <typename T>
  friend class list;
};

template <typename Type>
class ListIterator : public BaseIterator<ListIterator<Type>, Type> {
 public:
  using BaseIterator<ListIterator, Type>::BaseIterator;
  Type &operator*() { return this->current_node_->node_value_; };

  operator ListConstIterator<Type>() const noexcept {
    return ListConstIterator<Type>(this->current_node_);
  }

 protected:
  template <typename T>
  friend class list;
};

template <typename Type>
class list {
 public:
  using value_type = Type;
  using pointer = Type *;
  using reference = Type &;
  using const_reference = const Type &;
  using size_type = size_t;
  using iterator = ListIterator<value_type>;
  using const_iterator = ListConstIterator<value_type>;

  list() : size_(0) {
    end_ptr_ = new Node<Type>(0);
    begin_ptr_ = end_ptr_;
    MakeLoop();
  }

  list(size_type n) : list() {
    while (size_ != n) {
      this->push_back(0);
    }
  }

  list(std::initializer_list<value_type> const &items) : list() {
    for (auto it = items.begin(); it != items.end(); it++) {
      push_back(*it);
    }
  }

  list(const list &other) noexcept : list() {
    for (auto it = other.begin(); it != other.end(); ++it) {
      push_back(*it);
    }
  }

  list(list &&other) noexcept
      : begin_ptr_(other.begin_ptr_),
        end_ptr_(other.end_ptr_),
        size_(other.size_) {
    other.end_ptr_ = new Node<value_type>(0);
    other.begin_ptr_ = other.end_ptr_;
    other.MakeLoop();
    other.size_ = 0;
  }

  list &operator=(const list &other) noexcept {
    if (this != &other) {
      list temp(other);
      std::swap(size_, temp.size_);
      std::swap(begin_ptr_, temp.begin_ptr_);
      std::swap(end_ptr_, temp.end_ptr_);
    }
    return *this;
  }

  list &operator=(list &&other) noexcept {
    if (this != &other) {
      std::swap(size_, other.size_);
      std::swap(begin_ptr_, other.begin_ptr_);
      std::swap(end_ptr_, other.end_ptr_);
      other.clear();
    }
    return *this;
  }

  ~list() {
    clear();
    delete end_ptr_;
  }

  const_reference front() const { return begin_ptr_->node_value_; }
  const_reference back() const { return end_ptr_->prev_node_->node_value_; }

  iterator begin() noexcept { return iterator(begin_ptr_); }
  iterator end() noexcept { return iterator(end_ptr_); }
  const_iterator begin() const noexcept { return const_iterator(begin_ptr_); }
  const_iterator end() const noexcept { return const_iterator(end_ptr_); }

  bool empty() const noexcept { return (size_ == 0); };
  size_type size() const noexcept { return (size_); };
  size_type max_size() const noexcept {
    return std::numeric_limits<ptrdiff_t>::max() / sizeof(Node<value_type>);
  }

  void clear() noexcept {
    while (!empty()) {
      erase(begin());
    }
  }

  iterator insert(iterator pos, const_reference value) noexcept {
    Node<value_type> *new_node = new Node(value);
    Node<value_type> *prev_node = pos.current_node_->prev_node_;
    Node<value_type> *next_node = pos.current_node_;
    prev_node->next_node_ = new_node;
    next_node->prev_node_ = new_node;
    new_node->prev_node_ = prev_node;
    new_node->next_node_ = next_node;
    if (next_node == begin_ptr_) begin_ptr_ = new_node;
    MakeLoop();
    ++size_;
    return iterator(new_node);
  }

  void erase(iterator pos) noexcept {
    if (!empty() && pos.current_node_ != end_ptr_) {
      Node<value_type> *prev_node = pos.current_node_->prev_node_;
      Node<value_type> *next_node = pos.current_node_->next_node_;
      prev_node->next_node_ = next_node;
      next_node->prev_node_ = prev_node;
      if (pos == begin()) begin_ptr_ = next_node;
      MakeLoop();
      delete pos.current_node_;
      --size_;
    }
  }

  void push_back(const_reference value) noexcept { insert(end(), value); }

  void pop_back() noexcept {
    if (!empty()) erase(--end());
  }

  void push_front(const_reference value) noexcept { insert(begin(), value); }

  void pop_front() noexcept {
    if (!empty()) erase(begin());
  }

  void swap(list &other) noexcept {
    std::swap(this->begin_ptr_, other.begin_ptr_);
    std::swap(this->end_ptr_, other.end_ptr_);
    std::swap(this->size_, other.size_);
  }

  void merge(list &other) noexcept {
    if (&other != this) {
      auto it_1 = begin();
      auto it_2 = other.begin();
      while (it_1 != end() && it_2 != other.end()) {
        if (*it_1 > *it_2) {
          insert(it_1, *it_2);
          auto temp_it = it_2;
          ++it_2;
          other.erase(temp_it);
        } else {
          ++it_1;
        }
      }
      while (it_2 != other.end()) {
        push_back(*it_2);
        ++it_2;
      }
      other.clear();
    }
  }

  void splice(const_iterator pos, list &other) noexcept {
    if (!other.empty() && &other != this) {
      Node<value_type> *pos_node = pos.current_node_;
      Node<value_type> *pos_prev_node = pos.current_node_->prev_node_;
      Node<value_type> *other_begin = other.begin_ptr_;
      Node<value_type> *other_end = other.end_ptr_->prev_node_;

      pos_node->prev_node_ = other_end;
      pos_prev_node->next_node_ = other_begin;
      other_begin->prev_node_ = pos_prev_node;
      other_end->next_node_ = pos_node;

      if (pos == begin()) begin_ptr_ = other_begin;
      MakeLoop();
      size_ += other.size_;

      other.begin_ptr_ = other.end_ptr_;
      other.MakeLoop();
      other.size_ = 0;
    }
  }

  void reverse() noexcept {
    if (!empty() && size_ > 1) {
      for (auto it_1 = begin(), it_2 = --end();
           it_1.current_node_ != it_2.current_node_ &&
           it_1.current_node_->prev_node_ != it_2.current_node_;
           ++it_1, --it_2) {
        std::swap(*it_1, *it_2);
      }
    }
  }

  void unique() noexcept {
    if (!empty() && size_ > 1) {
      for (auto it = this->begin(); it != this->end();) {
        auto it_2 = it;
        ++it_2;
        if (it_2 != end() && *it == *it_2) {
          this->erase(it_2);
        } else {
          ++it;
        }
      }
    }
  }

  void sort() noexcept {
    if (!this->empty()) {
      for (auto it_1 = begin(); it_1 != this->end(); ++it_1) {
        for (auto it_2 = it_1; it_2 != this->end(); ++it_2) {
          if (*it_2 < *it_1) {
            value_type temp_value = *it_2;
            *it_2 = *it_1;
            *it_1 = temp_value;
          }
        }
      }
    }
  }

 private:
  void MakeLoop() {
    end_ptr_->next_node_ = begin_ptr_;
    begin_ptr_->prev_node_ = end_ptr_;
  };

  Node<value_type> *begin_ptr_;
  Node<value_type> *end_ptr_;
  size_type size_;
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_S21_LIST_H
