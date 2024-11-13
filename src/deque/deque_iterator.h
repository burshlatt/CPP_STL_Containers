#ifndef DEQUE_ITERATOR_H
#define DEQUE_ITERATOR_H

#include <iterator>

namespace s21 {
template <class T>
class deque_iterator {
public:
    using iterator_category = std::bidirectional_iterator_tag;

    using value_type        = T;
    using size_type         = std::size_t;
    using pointer           = std::conditional_t<std::is_const_v<value_type>, const value_type*, value_type*>;
    using reference         = std::conditional_t<std::is_const_v<value_type>, const value_type&, value_type&>;

public:
    deque_iterator(value_type* const* data, size_type x, size_type y) :
        _data(data),
        _x(x),
        _y(y)
    {};

public:
    reference operator*() { return _data[_x][_y]; }

    pointer operator->() { return &_data[_x][_y]; }

    deque_iterator& operator++() {
        if (_y == _block_size - 1) {
            ++_x;
            _y = 0;
        } else {
            ++_y;
        }

        return *this;
    }

    deque_iterator operator++(int) {
        deque_iterator tmp(*this);

        ++(*this);
        
        return tmp;
    }

    deque_iterator& operator--() {
        if (_y == 0) {
            --_x;
            _y = _block_size - 1;
        } else {
            --_y;
        }
        
        return *this;
    }

    deque_iterator operator--(int) {
        deque_iterator tmp(*this);
        
        --(*this);
        
        return tmp;
    }

    deque_iterator operator+(size_type n) const {
        deque_iterator tmp(*this);
        size_type total_steps = _x * _block_size + _y + n;

        tmp._x = total_steps / _block_size;
        tmp._y = total_steps % _block_size;

        return tmp;
    }

    deque_iterator operator-(size_type n) const {
        deque_iterator tmp(*this);
        size_type total_steps = _x * _block_size + _y - n;

        tmp._x = total_steps / _block_size;
        tmp._y = total_steps % _block_size;

        return tmp;
    }

    bool operator==(const deque_iterator &other) const noexcept {
        return _x == other._x && _y == other._y;
    }

    bool operator!=(const deque_iterator &other) const noexcept {
        return _x != other._x || _y != other._y;
    }

    bool operator>(const deque_iterator &other) const noexcept {
        return _x > other._x || (_x == other._x && _y > other._y);
    }

    bool operator<(const deque_iterator &other) const noexcept {
        return _x < other._x || (_x == other._x && _y < other._y);
    }

private:
    value_type* const* _data;

    size_type _x;
    size_type _y;

    static constexpr size_type _block_size{4096 / sizeof(T)};
};
} // namespace s21

#endif  // DEQUE_ITERATOR_H
