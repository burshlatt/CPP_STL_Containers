#ifndef TELECOM_HOMEWORK_FORWARD_LIST_HPP
#define TELECOM_HOMEWORK_FORWARD_LIST_HPP

#include <iostream>
#include <stdexcept>

namespace tlcm {
template <typename Type>
/*
  Структура узла, котоаря хранит указатель на след. узел и сам элемент.
*/
struct Node {
  using pointer = Type*;
  using reference = Type&;

  Node(Type val, Node<Type>* next_node = nullptr) :
    value(val),
    next(next_node)
  {}

  Type value;
  Node<Type>* next;
};

/*
  Итератор для моего списка, решил не реализовывать его константную версию,
  дабы не перегружать программу лишинм кодом, ведь по заданию это и так не нужно.
*/
template <typename Node>
class fwl_iterator {
 public:
  using pointer = typename Node::pointer;
  using reference = typename Node::reference;

 public:
  fwl_iterator(Node* current) :
    current_(current)
  {};

 public:
  Node* node() const noexcept { return current_; }
  reference operator*() { return current_->value; }
  pointer operator->() { return &(current_->value); }

  fwl_iterator& operator++() {
    if (!current_) {
        throw std::out_of_range("Incorrect iterator");
    }
    
    current_ = current_->next;
    return *this;
  }

  fwl_iterator operator++(int) {
    fwl_iterator tmp(*this);
    ++(*this);
    return tmp;
  }

  bool operator==(const fwl_iterator& other) const noexcept {
    return current_ == other.current_;
  }

  bool operator!=(const fwl_iterator& other) const noexcept {
    return current_ != other.current_;
  }

 private:
  Node* current_;
};

/*
  Сам список.
*/
template <typename Type>
class forward_list {
 public:
  using iterator = fwl_iterator<Node<Type>>;

 public:
  forward_list() :
    size_(0ULL),
    head_(nullptr),
    tail_(nullptr),
    null_(nullptr)
  {}

  forward_list(std::initializer_list<Type> items) : forward_list() {
    for (const auto& value : items) {
      push_back(value);
    }
  }

  forward_list(const forward_list&) = delete;
  forward_list& operator=(const forward_list&) = delete;

  ~forward_list() {
    while (!empty()) {
      pop_front();
    }
  }

  /*
    Функции возвращающие итераторы начала и конца, не стал делать их константные версии, дабы не увеличивать объем кода
  */
  iterator begin() noexcept { return iterator(head_); }
  iterator end() noexcept { return iterator(null_); }

  bool empty() const noexcept { return size_ == 0ULL; };
  std::size_t size() const noexcept { return size_; };

  /*
    Функция добавления элемента в произвольную позиции, добавляет следющим элементом после заданного итератора.
    Добавляется следующий, так как список односвязный и нет возможности при добавлении получить указатель на прошлый узел чтобы связать его с новым узлом.
  */
  iterator insert_after(iterator pos, const Type& value) {
    if (pos == end()) {
      throw std::out_of_range("insert_after: invalid position");
    }

    Node<Type>* current_node{pos.node()};
    Node<Type>* next_node{pos.node()->next};
    Node<Type>* new_node{new Node<Type>(value, next_node)};

    if (pos.node() == tail_) {
      tail_ = new_node;
    }

    current_node->next = new_node;

    ++size_;

    return iterator(new_node);
  }

  /*
    Функция удаления элемента из произвольной позиции, удаляет следющий элемент после заданного итератора.
    Удаляется следующий, так как список односвязный и нет возможности при удалении получить указатель на прошлый узел чтобы связать его с следующим узлом.
  */
  iterator erase_after(iterator pos) {
    if (pos == end() || pos.node() == tail_) {
      throw std::out_of_range("erase_after: invalid position");
    }

    if (empty()) {
      return end();
    }

    Node<Type>* current_node{pos.node()};
    Node<Type>* next_node{pos.node()->next};

    current_node->next = next_node->next;

    if (next_node == tail_) {
      tail_ = current_node;
    }

    delete next_node;
    next_node = nullptr;

    --size_;

    if (empty()) {
      return end();
    }

    return iterator(current_node->next);
  }

  /*
    Функция добавления элемента в начало списка, работает за O(1), так как имеется указатель на первый элемент
  */
  void push_front(const Type& value) {
    head_ = new Node<Type>(value, head_);

    if (empty()) {
      tail_ = head_;
    }

    ++size_;
  }

  /*
    Функция добавления элемента в конец списка, работает за O(1), так как имеется указатель на последний элемент
  */
  void push_back(const Type& value) {
    Node<Type>* new_node{new Node<Type>(value)};

    if (!empty()) {
      tail_->next = new_node;
    } else {
      head_ = new_node;
    }

    tail_ = new_node;
    ++size_;
  }

  /*
    Функция удаления элемента с начала списка, работает за O(1)
  */
  void pop_front() {
    if (empty()) {
      return;
    }

    Node<Type>* next_node{head_->next};

    delete head_;
    head_ = next_node;

    --size_;
  }

  /*
    Функция поиска элемента по заданному итератору
  */
  iterator find(const Type& value) {
    for (auto it{begin()}; it != end(); ++it) {
      if (*it == value) {
        return it;
      }
    }

    return end();
  }

 private:
  std::size_t size_; // Размер контейнера

  Node<Type>* head_; // Указатель на первый элемент в списке
  Node<Type>* tail_; // Указатель на последний элемент в списке
  Node<Type>* null_; // Просто указатель на nullptr
};
}  // namespace tlcm

#endif  // TELECOM_HOMEWORK_FORWARD_LIST_HPP
