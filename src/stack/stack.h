#ifndef STACK_H
#define STACK_H

#include <utility>
#include <algorithm>

#include "../deque/deque.h"

namespace s21 {
template<
    class T,
    class Container = s21::deque<T>
> class stack {
public:
    using container_type  = Container;
    using value_type      = Container::value_type;
    using size_type       = Container::size_type;
    using reference       = Container::reference;
    using const_reference = Container::const_reference;

public:
    stack() :
        stack(Container())
    {}

    explicit stack(const Container& cont) :
        _container(cont)
    {}

    explicit stack(Container&& cont) :
        _container(std::move(cont))
    {}

    stack(const stack& other) :
        _container(other._container)
    {}

    stack(stack&& other) :
        _container(std::move(other._container))
    {}

    ~stack() = default;

public:
    reference top() {
        return _container.back();
    }

    const_reference top() const {
        return _container.back();
    }

    bool empty() const {
        return _container.empty();
    }

    size_type size() const {
        return _container.size();
    }

    void push(const value_type& value) {
        _container.push_back(value);
    }

    void push(value_type&& value) {
        _container.push_back(std::move(value));
    }

    void pop() {
        _container.pop_back();
    }

    void swap(stack& other) noexcept {
        std::swap(_container, other._container);
    }

    stack& operator=(const stack& other) {
        _container = other._container;

        return *this;
    }

    stack& operator=(stack&& other) {
        _container = std::move(other._container);

        return *this;
    }

private:
    Container _container;
};
} // namespace s21

#endif  // STACK_H
