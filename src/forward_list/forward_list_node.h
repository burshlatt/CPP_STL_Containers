#ifndef FORWARD_LIST_NODE_H
#define FORWARD_LIST_NODE_H

#include <memory>

namespace s21 {
template <class T>
class forward_list_node {
public:
    using value_type      = T;

    using pointer         = T*;
    using const_pointer   = const T*;
    
    using reference       = T&;
    using const_reference = const T&;

public:
    explicit forward_list_node() :
        value(nullptr),
        next(nullptr)
    {}

    explicit forward_list_node(forward_list_node<T>* n) :
        value(nullptr),
        next(n)
    {}

    explicit forward_list_node(const value_type& v, forward_list_node<T>* n) :
        value(std::make_unique<T>(v)),
        next(n)
    {}

    explicit forward_list_node(value_type&& v, forward_list_node<T>* n) :
        value(std::make_unique<T>(std::move(v))),
        next(n)
    {}

public:
    std::unique_ptr<T> value;

    forward_list_node<T>* next;
};
} // namespace s21

#endif  // FORWARD_LIST_NODE_H
