#ifndef LIST_NODE_H
#define LIST_NODE_H

#include <memory>

namespace s21 {
template <class T>
class Node {
public:
    using value_type      = T;

    using pointer         = T*;
    using const_pointer   = const T*;
    
    using reference       = T&;
    using const_reference = const T&;

public:
    explicit Node() :
        value(nullptr),
        prev(this),
        next(this),
        _is_null(true)
    {}

    explicit Node(const value_type& v, Node<T>* p, Node<T>* n) :
        Node(T{v}, p, n)
    {}

    explicit Node(value_type&& v, Node<T>* p, Node<T>* n) :
        value(std::make_unique<T>(std::move(v))),
        prev(p),
        next(n),
        _is_null(false)
    {}

private:
    [[nodiscard]] bool is_null() const noexcept {
        return _is_null;
    }

public:
    std::unique_ptr<T> value;

    Node<T>* prev;
    Node<T>* next;

private:
    bool _is_null;
};
} // namespace s21

#endif  // LIST_NODE_H
