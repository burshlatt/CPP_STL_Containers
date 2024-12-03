#ifndef QUEUE_H
#define QUEUE_H

#include "../deque/deque.h"

namespace s21 {
template<
    class T,
    class Container = s21::deque<T>
    
> class queue {
public:
    using container_type  = Container;
    using size_type       = typename Container::size_type;
    using value_type      = typename Container::value_type;
    
    using reference       = typename Container::reference;
    using const_reference = typename Container::const_reference;

public:
    queue() :
        queue(Container())
    {}

    explicit queue(const Container& cont) :
        _container(cont)
    {}

    explicit queue(Container&& cont) :
        _container(std::move(cont))
    {}

    queue(const queue& other) :
        _container(other._container)
    {}

    queue(queue&& other) :
        _container(std::move(other._container))
    {}

    ~queue() = default;

public:
    reference front() {
        return _container.front();
    }

    const_reference front() const {
        return _container.front();
    }

    reference back() {
        return _container.back();
    }

    const_reference back() const {
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
        _container.pop_front();
    }

    void swap(queue& other) noexcept {
        std::swap(_container, other._container);
    }

    queue& operator=(const queue& other) {
        _container = other._container;

        return *this;
    }

    queue& operator=(queue&& other) {
        _container = std::move(other._container);

        return *this;
    }

private:
    Container _container;
};
} // namespace s21

#endif  // QUEUE_H
