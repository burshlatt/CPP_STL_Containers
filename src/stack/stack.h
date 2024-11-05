#ifndef STACK_H
#define STACK_H

#include "../deque/deque.h"

namespace s21 {
template<
    class T,
    class Container = s21::deque<T>
> class stack {
public:
    using value_type      = T;
    using size_type       = std::size_t;

    using reference       = T &;
    using const_reference = const T &;

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

private:
    Container _container;
};
}  // namespace s21

#endif  // STACK_H
