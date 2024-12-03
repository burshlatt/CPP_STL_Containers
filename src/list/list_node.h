#ifndef LIST_NODE_H
#define LIST_NODE_H

#include <memory>

namespace s21 {
template <class T>
class list_node {
public:
    using value_type      = T;

    using pointer         = T*;
    using const_pointer   = const T*;
    
    using reference       = T&;
    using const_reference = const T&;

public:
    explicit list_node() :
        value(nullptr),
        prev(this),
        next(this),
        _is_null(true)
    {}

    explicit list_node(const value_type& v, list_node<T>* p, list_node<T>* n) :
        list_node(T{v}, p, n)
    {}

    explicit list_node(value_type&& v, list_node<T>* p, list_node<T>* n) :
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

    list_node<T>* prev;
    list_node<T>* next;

private:
    bool _is_null;
};
} // namespace s21

#endif  // LIST_NODE_H
