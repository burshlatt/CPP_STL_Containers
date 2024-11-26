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
    using difference_type   = std::ptrdiff_t;
    
    using pointer           = std::conditional_t<std::is_const_v<T>, const T*, T*>;
    using reference         = std::conditional_t<std::is_const_v<T>, const T&, T&>;

public:
    deque_iterator() :
        _curr(nullptr),
        _x(0),
        _y(0)
    {}

    deque_iterator(T* const* curr, size_type x, size_type y) :
        _curr(curr),
        _x(x),
        _y(y)
    {}

    template <
        typename VT = T,
        typename = std::enable_if_t<std::is_const_v<VT>>
    > deque_iterator(const deque_iterator<std::remove_const_t<T>>& other) :
        _curr(other.base()),
        _x(other.block_idx()),
        _y(other.value_idx())
    {}

public:
    reference operator*() {
        return _curr[_x][_y];
    }

    pointer operator->() {
        return &_curr[_x][_y];
    }

    T* const* base() const noexcept {
        return _curr;
    }

    size_type block_idx() const noexcept {
        return _x;
    }

    size_type value_idx() const noexcept {
        return _y;
    }

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

    difference_type operator-(const deque_iterator& other) const {
        size_type this_idx = _x * _block_size + _y;
        size_type other_idx = other._x * _block_size + other._y;

        return static_cast<difference_type>(this_idx) - static_cast<difference_type>(other_idx);
    }

    [[nodiscard]] bool operator==(const deque_iterator &other) const noexcept {
        return _x == other._x && _y == other._y;
    }

    [[nodiscard]] bool operator!=(const deque_iterator &other) const noexcept {
        return _x != other._x || _y != other._y;
    }

    [[nodiscard]] bool operator>(const deque_iterator &other) const noexcept {
        return _x > other._x || (_x == other._x && _y > other._y);
    }

    [[nodiscard]] bool operator<(const deque_iterator &other) const noexcept {
        return _x < other._x || (_x == other._x && _y < other._y);
    }

private:
    T* const* _curr;

    size_type _x;
    size_type _y;

    static constexpr size_type _block_size{4096 / sizeof(T)};
};
} // namespace s21

#endif  // DEQUE_ITERATOR_H
